#ifndef DISCORD_CODECS_H
#define DISCORD_CODECS_H
#include <stddef.h>
#include <stdbool.h>
#define JSMN_STRICT
#define JSMN_HEADER
#include "jsmn.h"
#include "jsmn-find.h"
#define JSONB_HEADER
#include "json-build.h"
#include "common.h"
#include "cog-utils.h"
struct strings;

struct json_values;

struct snowflakes;

struct integers;

struct discord_role;

struct discord_roles;

struct discord_role_tag;

struct discord_application;

struct discord_audit_log;

struct discord_audit_log_entry;

struct discord_audit_log_entries;

struct discord_optional_audit_entry_info;

struct discord_optional_audit_entry_infos;

struct discord_audit_log_change;

struct discord_audit_log_changes;

struct discord_get_guild_audit_log;

struct discord_invite;

struct discord_invites;

struct discord_invite_metadata;

struct discord_invite_stage_instance;

struct discord_get_invite;

struct discord_channel;

struct discord_channels;

struct discord_message;

struct discord_messages;

struct discord_message_activity;

struct discord_message_reference;

struct discord_followed_channel;

struct discord_reaction;

struct discord_reactions;

struct discord_overwrite;

struct discord_overwrites;

struct discord_thread_metadata;

struct discord_thread_member;

struct discord_thread_members;

struct discord_attachment;

struct discord_attachments;

struct discord_embed;

struct discord_embeds;

struct discord_embed_thumbnail;

struct discord_embed_video;

struct discord_embed_image;

struct discord_embed_provider;

struct discord_embed_author;

struct discord_embed_footer;

struct discord_embed_field;

struct discord_embed_fields;

struct discord_channel_mention;

struct discord_allowed_mention;

struct discord_thread_response_body;

struct discord_modify_channel;

struct discord_get_channel_messages;

struct discord_create_message;

struct discord_get_reactions;

struct discord_edit_message;

struct discord_bulk_delete_messages;

struct discord_edit_channel_permissions;

struct discord_create_channel_invite;

struct discord_follow_news_channel;

struct discord_group_dm_add_recipient;

struct discord_start_thread_with_message;

struct discord_start_thread_without_message;

struct discord_list_active_threads;

struct discord_emoji;

struct discord_emojis;

struct discord_create_guild_emoji;

struct discord_modify_guild_emoji;

struct discord_guild;

struct discord_guilds;

struct discord_guild_preview;

struct discord_guild_widget_setting;

struct discord_get_guild_widget;

struct discord_guild_member;

struct discord_guild_members;

struct discord_integration;

struct discord_integrations;

struct discord_integration_account;

struct discord_integration_application;

struct discord_ban;

struct discord_bans;

struct discord_welcome_screen;

struct discord_welcome_screen_channel;

struct discord_welcome_screen_channels;

struct discord_create_guild;

struct discord_modify_guild;

struct discord_create_guild_channel;

struct discord_modify_guild_channel_position;

struct discord_modify_guild_channel_positions;

struct discord_list_active_guild_threads;

struct discord_list_guild_members;

struct discord_search_guild_members;

struct discord_add_guild_member;

struct discord_modify_guild_member;

struct discord_modify_current_member;

struct discord_modify_current_user_nick;

struct discord_create_guild_ban;

struct discord_create_guild_role;

struct discord_modify_guild_role_position;

struct discord_modify_guild_role_positions;

struct discord_modify_guild_role;

struct discord_get_guild_prune_count;

struct discord_begin_guild_prune;

struct discord_get_guild_widget_image;

struct discord_modify_guild_welcome_screen;

struct discord_modify_current_user_voice_state;

struct discord_modify_user_voice_state;

struct discord_guild_scheduled_event;

struct discord_guild_scheduled_events;

struct discord_guild_scheduled_event_entity_metadata;

struct discord_guild_scheduled_event_user;

struct discord_list_scheduled_events_for_guild;

struct discord_create_guild_scheduled_event;

struct discord_get_guild_scheduled_event;

struct discord_modify_guild_scheduled_event;

struct discord_get_guild_scheduled_event_users;

struct discord_guild_template;

struct discord_create_guild_from_guild_template;

struct discord_create_guild_template;

struct discord_modify_guild_template;

struct discord_stage_instance;

struct discord_stage_instances;

struct discord_create_stage_instance;

struct discord_modify_stage_instance;

struct discord_sticker;

struct discord_stickers;

struct discord_sticker_item;

struct discord_sticker_items;

struct discord_sticker_pack;

struct discord_create_guild_sticker;

struct discord_modify_guild_sticker;

struct discord_user;

struct discord_users;

struct discord_connection;

struct discord_connections;

struct discord_modify_current_user;

struct discord_get_current_user_guilds;

struct discord_create_dm;

struct discord_create_group_dm;

struct discord_voice_state;

struct discord_voice_states;

struct discord_voice_region;

struct discord_voice_regions;

struct discord_webhook;

struct discord_webhooks;

struct discord_create_webhook;

struct discord_modify_webhook;

struct discord_modify_webhook_with_token;

struct discord_execute_webhook;

struct discord_get_webhook_message;

struct discord_edit_webhook_message;

struct discord_delete_webhook_message;

struct discord_identify;

struct discord_identify_connection;

struct discord_voice_state_status;

struct discord_presence_update;

struct discord_presence_updates;

struct discord_activity;

struct discord_activities;

struct discord_activity_timestamps;

struct discord_activity_emoji;

struct discord_activity_party;

struct discord_activity_assets;

struct discord_activity_secrets;

struct discord_activity_button;

struct discord_activity_buttons;

struct discord_session_start_limit;

struct discord_team;

struct discord_team_member;

struct discord_team_members;

struct discord_application_command;

struct discord_application_commands;

struct discord_application_command_option;

struct discord_application_command_options;

struct discord_application_command_option_choice;

struct discord_application_command_option_choices;

struct discord_application_command_interaction_data_option;

struct discord_application_command_interaction_data_options;

struct discord_guild_application_command_permission;

struct discord_guild_application_command_permissions;

struct discord_application_command_permission;

struct discord_application_command_permissions;

struct discord_create_global_application_command;

struct discord_edit_global_application_command;

struct discord_create_guild_application_command;

struct discord_edit_guild_application_command;

struct discord_edit_application_command_permissions;

struct discord_component;

struct discord_components;

struct discord_select_option;

struct discord_select_options;

struct discord_interaction;

struct discord_interaction_data;

struct discord_resolved_data;

struct discord_message_interaction;

struct discord_interaction_response;

struct discord_interaction_callback_data;

struct discord_edit_original_interaction_response;

struct discord_create_followup_message;

struct discord_edit_followup_message;

struct strings {
  int size;
  char **array;
  int realsize;
};
struct json_values {
  int size;
  json_char **array;
  int realsize;
};
struct snowflakes {
  int size;
  u64snowflake *array;
  int realsize;
};
struct integers {
  int size;
  int *array;
  int realsize;
};
/** Allows creation of instant invites */
#define DISCORD_PERM_CREATE_INSTANT_INVITE 1 << 0
/** Allows kicking members */
#define DISCORD_PERM_KICK_MEMBERS 1 << 1
/** Allows banning members */
#define DISCORD_PERM_BAN_MEMBERS 1 << 2
/** Allows all permissions and bypasses channel permission overwrites */
#define DISCORD_PERM_ADMINISTRATOR 1 << 3
/** Allows management and editing of channels */
#define DISCORD_PERM_MANAGE_CHANNELS 1 << 4
/** Allows management and editing of the guild */
#define DISCORD_PERM_MANAGE_GUILD 1 << 5
/** Allows for the addition of reactions to messages */
#define DISCORD_PERM_ADD_REACTIONS 1 << 6
/** Allows for viewing of audit logs */
#define DISCORD_PERM_VIEW_AUDIT_LOG 1 << 7
/** Allows for using priority speaker in a voice channel */
#define DISCORD_PERM_PRIORITY_SPEAKER 1 << 8
/** Allows the user to go live */
#define DISCORD_PERM_STREAM 1 << 9
/** Allows guild members to view a channel, which includes reading messages
     in text channels and joining voice channels */
#define DISCORD_PERM_VIEW_CHANNEL 1 << 10
/** Allows for sending messages in a channel (does not allow sending messages
     in threads) */
#define DISCORD_PERM_SEND_MESSAGES 1 << 11
/** Allows for sending of `/tts` messages */
#define DISCORD_PERM_SEND_TTS_MESSAGES 1 << 12
/** Allows for deletion of other users messages */
#define DISCORD_PERM_MANAGE_MESSAGES 1 << 13
/** Links sent by users with this permission will be auto-embedded */
#define DISCORD_PERM_EMBED_LINKS 1 << 14
/** Allows for uploading images and files */
#define DISCORD_PERM_ATTACH_FILES 1 << 15
/** Allows for reading of message history */
#define DISCORD_PERM_READ_MESSAGE_HISTORY 1 << 16
/** Allows for using the `@everyone` tag to notify all users in a channel,
     and the `@here` tag to notify all online users in a channel */
#define DISCORD_PERM_MENTION_EVERYONE 1 << 17
/** Allows the usage of custom emojis from other servers */
#define DISCORD_PERM_USE_EXTERNAL_EMOJIS 1 << 18
/** Allows for viewing guild insights */
#define DISCORD_PERM_VIEW_GUILD_INSIGHTS 1 << 19
/** Allows for joining of a voice channel */
#define DISCORD_PERM_CONNECT 1 << 20
/** Allows for speaking in a voice channel */
#define DISCORD_PERM_SPEAK 1 << 21
/** Allows for muting members in a voice channel */
#define DISCORD_PERM_MUTE_MEMBERS 1 << 22
/** Allows for deafening of members in a voice channel */
#define DISCORD_PERM_DEAFEN_MEMBERS 1 << 23
/** Allows for moving of members between voice channels */
#define DISCORD_PERM_MOVE_MEMBERS 1 << 24
/** Allows for using voice-activity-detection in a voice channel */
#define DISCORD_PERM_USE_VAD 1 << 25
/** Allows for modification of own nickname */
#define DISCORD_PERM_CHANGE_NICKNAME 1 << 26
/** Allows for modification of other users nicknames */
#define DISCORD_PERM_MANAGE_NICKNAMES 1 << 27
/** Allows management and editing of roles */
#define DISCORD_PERM_MANAGE_ROLES 1 << 28
/** Allows management and editing of webhooks */
#define DISCORD_PERM_MANAGE_WEBHOOKS 1 << 29
/** Allows management and editing of emojis and stickers */
#define DISCORD_PERM_MANAGE_EMOJIS_AND_STICKERS 1 << 30
/** Allows members to use application commands, including slash commands and
     context menu commands */
#define DISCORD_PERM_USE_APPLICATION_COMMANDS 1 << 31
/** Allows for requesting to speak in stage channels */
#define DISCORD_PERM_REQUEST_TO_SPEAK 1 << 32
/** Allows for creating, editing, and deleting scheduled events */
#define DISCORD_PERM_MANAGE_EVENTS 1 << 33
/** Allows for deleting and archiving threads, and viewing all private
     threads */
#define DISCORD_PERM_MANAGE_THREADS 1 << 34
/** Allows for creating public and announcement threads */
#define DISCORD_PERM_CREATE_PUBLIC_THREADS 1 << 35
/** Allows for creating private threads */
#define DISCORD_PERM_CREATE_PRIVATE_THREADS 1 << 36
/** Allows the usage of custom stickers from other servers */
#define DISCORD_PERM_USE_EXTERNAL_STICKERS 1 << 37
/** Allows for sending messages in threads */
#define DISCORD_PERM_SEND_MESSAGES_IN_THREADS 1 << 38
/** Allows for launching activities (applications with the `EMBEDDED` flag)
     in a voice channel) */
#define DISCORD_PERM_START_EMBEDDED_ACTIVITIES 1 << 39
/** Allows for timing out users to prevent them from sending or reacting to
     messages in chat and threads, and from speaking in voice and stage
     channels */
#define DISCORD_PERM_MODERATE_MEMBERS 1 << 40
struct discord_role {
  /** role id */
  u64snowflake id;
  /** role name */
  char *name;
  /** integer representationof hexadecimal color code */
  int color;
  /** if this role is pinned in the user listing */
  bool hoist;
  /** role icon hash */

  char *icon;

  /** role unicode emoji */

  char *unicode_emoji;

  /** position of this role */
  int position;
  /** permission bit set */
  char *permissions;
  /** whether this role is managed by an integration */
  bool managed;
  /** whether this roleis mentionable */
  bool mentionable;
  /** the tags this role has */

  struct discord_role_tag *tags;
};
struct discord_roles {
  int size;
  struct discord_role *array;
  int realsize;
};
struct discord_role_tag {
  /** the id of the bot this role belongs to */

  u64snowflake bot_id;

  /** the id of the integration this role belongs to */

  u64snowflake integration_id;

  /** whether this is the guild's premium subscribe role */
  bool premium_subscribe;
};
#define DISCORD_APPLICATION_GATEWAY_PRESENCE 1 << 12
#define DISCORD_APPLICATION_GATEWAY_PRESENCE_LIMITED 1 << 13
#define DISCORD_APPLICATION_GATEWAY_GUILD_MEMBERS 1 << 14
#define DISCORD_APPLICATION_GATEWAY_GUILD_MEMBERS_LIMITED 1 << 15
#define DISCORD_APPLICATION_VERIFICATION_PENDING_GUILD_LIMIT 1 << 16
#define DISCORD_APPLICATION_EMBEDDED 1 << 17
#define DISCORD_APPLICATION_GATEWAY_MESSAGE_CONTENT 1 << 18
#define DISCORD_APPLICATION_GATEWAY_MESSAGE_CONTENT_LIMITED 1 << 19
struct discord_application {
  /** the ID of the app */
  u64snowflake id;
  /** the name of the app */
  char *name;
  /** the icon hash of the app */
  char *icon;
  /** the description of the app */
  char *description;
  /** an array of rpc origin urls, if rpc is enabled */

  struct strings *rpc_origins;

  /** when false only app owner can join the app's bot to guilds */
  bool bot_public;
  /** when true the app's bot will only join upon completion of the full
       oauth2 code grant flow */
  bool bot_require_code_grant;
  /** the url of the app's terms of service */
  char *terms_of_service_url;
  /** the url of the app's privacy policy */
  char *privacy_policy_url;
  /** partial user object containing info on the owner of the application */

  struct discord_user *owner;

  /** if this application is a game sold on Discord, this field will be the
       summary field for the store page of its primary sku */
  char *summary;
  /** the hex encoded key for verification in interactions and the GameSDK's
       GetTicket */
  char *verify_key;
  /** if the application belongs to a team, this will be a list of the
       members of that team */

  struct discord_team *team;

  /** if this application is a game sold on Discord, this field will be the
       guild to which it has been linked */
  u64snowflake guild_id;
  /** if this application is a game sold on Discord, this field will be the
       ID of the \Game SKU\ that is created, if exists */
  u64snowflake primary_sku_id;
  /** if this application is a game sold on Discord, this field will be the
       URL slug that links to the store page */
  char *slug;
  /** the application's default rich presence invite cover image hash */
  char *cover_image;
  /** the application's public flags */
  u64snowflake flags;
};
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
  DISCORD_AUDIT_LOG_INVITE_UPDATE = 41,
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
  DISCORD_AUDIT_LOG_STAGE_INSTANCE_CREATE = 83,
  DISCORD_AUDIT_LOG_STAGE_INSTANCE_UPDATE = 84,
  DISCORD_AUDIT_LOG_STAGE_INSTANCE_DELETE = 85,
  DISCORD_AUDIT_LOG_STICKER_CREATE = 90,
  DISCORD_AUDIT_LOG_STICKER_UPDATE = 91,
  DISCORD_AUDIT_LOG_STICKER_DELETE = 92,
  DISCORD_AUDIT_LOG_GUILD_SCHEDULED_EVENT_CREATE = 100,
  DISCORD_AUDIT_LOG_GUILD_SCHEDULED_EVENT_UPDATE = 101,
  DISCORD_AUDIT_LOG_GUILD_SCHEDULED_EVENT_DELETE = 102,
  DISCORD_AUDIT_LOG_THREAD_CREATE = 110,
  DISCORD_AUDIT_LOG_THREAD_UPDATE = 111,
  DISCORD_AUDIT_LOG_THREAD_DELETE = 112
};
struct discord_audit_log {
  /** list of audit log entries */

  struct discord_audit_log_entries *audit_log_entries;

  /** list of guild scheduled events found in the audit log */

  struct discord_guild_scheduled_events *guild_scheduled_events;

  /** list of partial integration objects */

  struct discord_integrations *integrations;

  /** list of threads found in the audit log */

  struct discord_channels *threads;

  /** list of users found in the audit log */

  struct discord_users *users;

  /** list of webhooks found in the audit log */

  struct discord_webhooks *webhooks;
};
struct discord_audit_log_entry {
  /** ID of the affected entity (webhook, user, role, etc.) */
  u64snowflake target_id;
  /** changes made to the target_id */

  struct discord_audit_log_changes *changes;

  /** the user who made the changes */
  u64snowflake user_id;
  /** id of the entry */
  u64snowflake id;
  /** type of action that occurred */

  enum discord_audit_log_events action_type;

  /** additional info for certain action types */

  struct discord_optional_audit_entry_infos *options;

  /** the reason for the change (0-512) characters */
  char *reason;
};
struct discord_audit_log_entries {
  int size;
  struct discord_audit_log_entry *array;
  int realsize;
};
struct discord_optional_audit_entry_info {
  /** channel in which the entities were targeted */
  u64snowflake channel_id;
  /** number of entities that were targeted */
  char *count;
  /** number of days after which inactive members were kicked */
  char *delete_member_days;
  /** id of the overwritten entity */
  u64snowflake id;
  /** number of members removed by prune */
  char *members_removed;
  /** ID of the message that was targeted */
  u64snowflake message_id;
  /** name of the role if type is \0\ (not present if type is \1\) */
  char *role_name;
  /** type of overwritten entity - 0 for role or 1 for \member\ */
  char *type;
};
struct discord_optional_audit_entry_infos {
  int size;
  struct discord_optional_audit_entry_info *array;
  int realsize;
};
struct discord_audit_log_change {
  /** new value of the key */
  json_char *new_value;
  /** old value of the key */
  json_char *old_value;
  /** name of audit log change key */
  char *key;
};
struct discord_audit_log_changes {
  int size;
  struct discord_audit_log_change *array;
  int realsize;
};
struct discord_get_guild_audit_log {
  /** filter the log for actions made by a user */
  u64snowflake user_id;
  /** the type of audit log event */
  int action_type;
  /** filter the log before a certain entry ID */
  u64snowflake before;
  /** how many entries are returned (default 50, minimum 1, maximum 100) */

  int limit;
};
enum discord_invite_target_types {
  DISCORD_INVITE_TARGET_STREAM = 1,
  DISCORD_INVITE_TARGET_EMBEDDED_APPLICATION = 2
};
struct discord_invite {
  /** the invite code (unique ID) */
  char *code;
  /** the guild this invite is for */

  struct discord_guild *guild;

  /** the channel this invite is for */
  struct discord_channel *channel;
  /** the user who created the invite */

  struct discord_user *inviter;

  /** the type of target for this voice channel invite */

  enum discord_invite_target_types target_type;

  /** the user whose stream to display for this voice channel stream invite */

  struct discord_user *target_user;

  /** the embedded application to open for this voice channel embedded
       application invite */

  struct discord_application *target_application;

  /** approximate count of online members */
  int approximate_presence_count;
  /** approximate count of total members */
  int approximate_member_count;
  /** the expiration date of this invite */

  u64unix_ms expires_at;

  /** stage instance data if there is a public stage instance in the stage
       channel this invite is for */

  struct discord_invite_stage_instance *stage_instance;

  /** guild scheduled event data, only included if `guild_scheduled_event_id`
       contains a valid guild scheduled event ID */

  struct discord_guild_scheduled_event *guild_scheduled_event;
};
struct discord_invites {
  int size;
  struct discord_invite *array;
  int realsize;
};
struct discord_invite_metadata {
  /** number of times this invite has been used */
  int uses;
  /** max number of times this invite can been used */
  int max_uses;
  /** duration (in seconds) after which the invite expires */
  int max_age;
  /** whether this invite only grants temporary membership */
  bool temporary;
  /** when this invite was created */

  u64unix_ms created_at;
};
struct discord_invite_stage_instance {
  /** the members speaking in the Stage */

  struct discord_guild_members *members;

  /** the number of users in the Stage */
  int participant_count;
  /** the number of users speaking in the Stage */
  int speaker_count;
  /** the topic of the Stage instance (1-120 characters) */
  char *topic;
};
struct discord_get_invite {
  /** whether the invite should contain approximate member counts */
  bool with_counts;
  /** whether the invite should contain the expiration date */
  bool with_expiration;
  /** the guild scheduled event to include with the invite */

  u64snowflake guild_scheduled_event_id;
};
enum discord_channel_types {
  /** a text channel within a server */
  DISCORD_CHANNEL_GUILD_TEXT = 0,
  /** a direct message between users */
  DISCORD_CHANNEL_DM = 1,
  /** a voice channel within a server */
  DISCORD_CHANNEL_GUILD_VOICE = 2,
  /** a direct message between multiple users */
  DISCORD_CHANNEL_GROUP_DM = 3,
  /** an organization category that contains up to 50 channels */
  DISCORD_CHANNEL_GUILD_CATEGORY = 4,
  /** a channel that users can follow and crosspost into their own server */
  DISCORD_CHANNEL_GUILD_NEWS = 5,
  /** a channel in which game developers can seel their game on Discord */
  DISCORD_CHANNEL_GUILD_STORE = 6,
  /** a temporary sub-channel within a @ref DISCORD_CHANNEL_GUILD_NEWS
       channel */
  DISCORD_CHANNEL_GUILD_NEWS_THREAD = 10,
  /** a temporary sub-channel within a @ref DISCORD_CHANNEL_GUILD_TEXT
       channel */
  DISCORD_CHANNEL_GUILD_PUBLIC_THREAD = 11,
  /** a temporary sub-channel within a @ref DISCORD_CHANNEL_GUILD_TEXT
       channel that is only viewable by those invited and those with the
       `MANAGE_THREADS` permission */
  DISCORD_CHANNEL_GUILD_PRIVATE_THREAD = 12,
  /** a voice channel for hosting events with an audience */
  DISCORD_CHANNEL_GUILD_STAGE_VOICE = 13
};
enum discord_video_quality_modes {
  /** Discord chooses the quality for optimal performance */
  DISCORD_VIDEO_QUALITY_AUTO = 1,
  /** 720p */
  DISCORD_VIDEO_QUALITY_FULL = 2
};
enum discord_message_types {
  DISCORD_MESSAGE_DEFAULT = 0,
  DISCORD_MESSAGE_RECIPIENT_ADD = 1,
  DISCORD_MESSAGE_RECIPIENT_REMOVE = 2,
  DISCORD_MESSAGE_CALL = 3,
  DISCORD_MESSAGE_CHANNEL_NAME_CHANGE = 4,
  DISCORD_MESSAGE_CHANNEL_ICON_CHANGE = 5,
  DISCORD_MESSAGE_CHANNEL_PINNED_MESSAGE = 6,
  DISCORD_MESSAGE_GUILD_MEMBER_JOIN = 7,
  DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION = 8,
  DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_1 = 9,
  DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_2 = 10,
  DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_3 = 11,
  DISCORD_MESSAGE_CHANNEL_FOLLOW_ADD = 12,
  DISCORD_MESSAGE_GUILD_DISCOVERY_DISQUALIFIED = 14,
  DISCORD_MESSAGE_GUILD_DISCOVERY_REQUALIFIED = 15,
  DISCORD_MESSAGE_GUILD_DISCOVERY_GRACE_PERIOD_INITIAL_WARNING = 16,
  DISCORD_MESSAGE_GUILD_DISCOVERY_GRACE_PERIOD_FINAL_WARNING = 17,
  DISCORD_MESSAGE_THREAD_CREATED = 18,
  DISCORD_MESSAGE_REPLY = 19,
  DISCORD_MESSAGE_CHAT_INPUT_COMMAND = 20,
  DISCORD_MESSAGE_THREAD_STARTER_MESSAGE = 21,
  DISCORD_MESSAGE_GUILD_INVITE_REMINDER = 22,
  DISCORD_MESSAGE_CONTEXT_MENU_COMMAND = 22
};
enum discord_message_activity_types {
  DISCORD_MESSAGE_ACTIVITY_JOIN = 1,
  DISCORD_MESSAGE_ACTIVITY_SPECTATE = 2,
  DISCORD_MESSAGE_ACTIVITY_LISTEN = 3,
  DISCORD_MESSAGE_ACTIVITY_JOIN_REQUEST = 5
};
enum discord_message_flags {
  /** this message has been published to subscribed channels (via Channel
       Following) */
  DISCORD_MESSAGE_CROSSPOSTED = 1 << 0,
  /** this message originated from a message in another channel (via Channel
       Following) */
  DISCORD_MESSAGE_IS_CROSSPOST = 1 << 1,
  /** do not include any embed when serializing this message */
  DISCORD_MESSAGE_SUPRPRESS_EMBEDS = 1 << 2,
  /** the source message for this crosspost has been deleted (via Channel
       Following) */
  DISCORD_MESSAGE_SOURCE_MESSAGE_DELETED = 1 << 3,
  /** this message came from the urgent message system */
  DISCORD_MESSAGE_URGENT = 1 << 4,
  /** this message has an associated thread, with the same ID as the message */
  DISCORD_MESSAGE_HAS_THREAD = 1 << 5,
  /** this message is only visible to the user who invoked the interaction */
  DISCORD_MESSAGE_EPHEMERAL = 1 << 6,
  /** this message is an interaction response and the bot is thinking */
  DISCORD_MESSAGE_LOADING = 1 << 7,
  /** this message failed to mention some roles and add the members to the
       thread */
  DISCORD_MESSAGE_FAILED_TO_MENTION_SOME_ROLES_IN_THREAD = 1 << 8
};
struct discord_channel {
  /** the ID of this channel */
  u64snowflake id;
  /** the type of channel */
  enum discord_channel_types type;
  /** the ID of the guild (may be missing for some channel objects received
       over gateway guild dispatches) */

  u64snowflake guild_id;

  /** sorting position of the channel */
  int position;
  /** explicit permission overwrites for members and roles */
  struct discord_overwrites *permission_overwrites;
  /** the name of the channel (0-1024 characters) */
  char *name;
  /** the channel topic (0-1024 characters) */
  char *topic;
  /** whether the channel is nsfw */
  bool nsfw;
  /** the id of the last message sent in this channel (may not point to an
       existing or valid message) */
  u64snowflake last_message_id;
  /** the bitrate (in bits) of the voice channel */
  int bitrate;
  /** the user limit of the voice channel */
  int user_limit;
  /** amount of seconds a user has to wait before sending another message
        (0-21600). bots, as well as users with the permission
       `MANAGE_MESSAGES` or `MANAGE_CHANNEL` are unaffected */
  int rate_limit_per_user;
  /** array of user objects */
  struct discord_users *recipients;
  /** icon hash of the group DM */
  char *icon;
  /** id of the creator of the group DM or thread */
  u64snowflake owner_id;
  /** application ID of the group DM creator if its bot-created */
  u64snowflake application_id;
  /** for guild channels: ID of the parent category for a channel (each
       parent category can contain up to 50 channels), for threads: id of
       the text channel this thread was created */
  u64snowflake parent_id;
  /** when the last pinned message was pinned. This may be `NULL` in events
       such as `GUILD_CREATE` when a message is not pinned */
  u64unix_ms last_pin_timestamp;
  /** voice region ID for the voice channel, automatic when set to null */
  char *rtc_region;
  /** the camera video quality mode of the voice channel, 1 when not present */
  int voice_quality_mode;
  /** an approximate count of messages in a thread, stops counting at 50 */
  int message_count;
  /** an approximate count of users in a thread, stops counting at 50 */
  int member_count;
  /** thread-specific fields not needed by other channels */
  struct discord_thread_metadata *thread_metadata;
  /** thread member object for the current user, if they have joined the
       thread, only included on certain API endpoints */
  struct discord_thread_member *member;
  /** default duration that the clients (not the API) will use for newly
       created threads, in minutes, to automatically archive the thread
       after recent activity, can be set to: 60, 1440, 4320, 10080 */
  int default_auto_archive_duration;
  /** computed permissions for the invoking user in the channel, including
       overwrites, only included when part of the `resolved` data received
       on a application command interaction */
  char *permissions;
};
struct discord_channels {
  int size;
  struct discord_channel *array;
  int realsize;
};
struct discord_message {
  /** ID of the message */
  u64snowflake id;
  /** ID of the channel the message was sent in */
  u64snowflake channel_id;
  /** ID of the guild the message was sent in */
  u64snowflake guild_id;
  /** the author of this message (not guaranteed to be a valid user) */
  struct discord_user *author;
  /** partial guild member */
  struct discord_guild_member *member;
  /** contents of the message */
  char *content;
  /** when this message was sent */
  u64unix_ms timestamp;
  /** when this message was edited (or null if never) */

  u64unix_ms edited_timestamp;

  /** whether this was a TTS message */
  bool tts;
  /** whether this message mentions everyone */
  bool mention_everyone;
  /** users specifically mentioned in the message */
  struct discord_users *mentions;
  /** roles specifically mentioned in this message */
  struct discord_roles *mention_roles;
  /** channels specifically mentioned in this message */
  struct discord_channels *mention_channels;
  /** any attached files */
  struct discord_attachments *attachments;
  /** any embedded content */
  struct discord_embeds *embeds;
  /** reactions to the message */
  struct discord_reactions *reactions;
  /** used for validating a message was sent */
  char *nonce;
  /** whether this message is pinned */
  bool pinned;
  /** if the message is generated by a webhook, this is the webhook's ID */
  u64snowflake webhook_id;
  /** type of message */
  enum discord_message_types type;
  /** sent with Rich Presence-related chat embeds */
  struct discord_message_activity *activity;
  /** sent with Rich Presence-related chat embeds */
  struct discord_application *application;
  /** if the message is an interaction or an application-owned webhook, this
       is the ID of the application */
  u64snowflake application_id;
  /** data showing the source of a crosspost, channel follow add, pin, or
       reply message */
  struct discord_message_reference *message_reference;
  /** message flags combined as a bitfield */
  enum discord_message_flags flags;
  /** the message associated with the message_reference */
  struct discord_message *referenced_message;
  /** sent if the message is a response to an interaction */
  struct discord_message_interaction *interaction;
  /** the thread that was started from this message, includes
       @ref discord_thread_member */
  struct discord_channel *thread;
  /** sent if the message contains components like buttons, action rows, or
       other interactive components */
  struct discord_components *components;
  /** sent if the message contains stickers */
  struct discord_sticker_items *sticker_items;
};
struct discord_messages {
  int size;
  struct discord_message *array;
  int realsize;
};
struct discord_message_activity {
  /** type of message activity */
  enum discord_message_activity_types type;
  /** party_id from a Rich Presence event */
  char *party_id;
};
struct discord_message_reference {
  /** id of the originating message */
  u64snowflake message_id;
  /** id of the originating message's channel */
  u64snowflake channel_id;
  /** id of the originating message's guild */
  u64snowflake guild_id;
  /** when sending, whether to error if the referenced message doesn't exist
       instead of sending as normal (non-reply) message, default true */
  bool fail_if_not_exists;
};
struct discord_followed_channel {
  /** source channel id */
  u64snowflake channel_id;
  /** created target webhook id */
  u64snowflake webhook_id;
};
struct discord_reaction {
  /** times this emoji has been used to react */
  int count;
  /** whether the current user reacted using this emoji */
  bool me;
  /** emoji information */
  struct discord_emoji *emoji;
};
struct discord_reactions {
  int size;
  struct discord_reaction *array;
  int realsize;
};
struct discord_overwrite {
  /** role or user id */
  u64snowflake id;
  /** either 0 (role) or 1 (member) */
  int type;
  /** permission bit set */
  u64snowflake allow;
  /** permission bit set */
  u64snowflake deny;
};
struct discord_overwrites {
  int size;
  struct discord_overwrite *array;
  int realsize;
};
struct discord_thread_metadata {
  /** whether the thread is archived */
  bool archived;
  /** duration in minutes to automatically archive the thread after recent
       activity, can be set to: 60, 1440, 3320, 10080 */
  int auto_archive_duration;
  /** timestamp when the thread's archive status was last changed, used for
       calculating recent activity */
  u64unix_ms archive_timestamp;
  /** whether the thread is locked; when a thread is locked only users with
       `MANAGE_THREADS` can unarchive it */
  bool locked;
  /** whether non-moderators cana dd other non-moderators to a thread; only
       available on private threads */
  bool invitable;
  /** timestamp when the thread was created; only populated for threads
       created after 2022-01-09 */
  u64unix_ms create_timestamp;
};
struct discord_thread_member {
  /** the id of the thread */
  u64snowflake id;
  /** the id of the user */
  u64snowflake user_id;
  /** the time the current user last joined the thread */
  u64unix_ms join_timestamp;
  /** any user-thread settings, currently only used for notifications */
  int flags;
};
struct discord_thread_members {
  int size;
  struct discord_thread_member *array;
  int realsize;
};
struct discord_attachment {
  /** the file contents */
  char *content;
  /** attachment ID */
  u64snowflake id;
  /** name of file attached */

  char *filename;

  /** description for the file */

  char *description;

  /** the attachment media type */

  char *content_type;

  /** size of file in bytes */
  int size;
  /** source url of file */
  char *url;
  /** proxied url of file */
  char *proxy_url;
  /** height of file (if image) */

  int height;

  /** width of file (if image) */

  int width;

  /** whether this attachment is ephemeral */
  bool ephemeral;
};
struct discord_attachments {
  int size;
  struct discord_attachment *array;
  int realsize;
};
struct discord_embed {
  /** title of embed */
  char *title;
  /** type of embed (always \rich\ for webhook embeds) */
  char *type;
  /** description of embed */
  char *description;
  /** url of embed */
  char *url;
  /** timestamp of embed content */

  u64unix_ms timestamp;

  /** color code of the embed */

  int color;

  /** footer information */

  struct discord_embed_footer *footer;

  /** image information */

  struct discord_embed_image *image;

  /** thumbnail information */

  struct discord_embed_thumbnail *thumbnail;

  /** video information */

  struct discord_embed_video *video;

  struct discord_embed_provider *provider;

  struct discord_embed_author *author;

  struct discord_embed_fields *fields;
};
struct discord_embeds {
  int size;
  struct discord_embed *array;
  int realsize;
};
struct discord_embed_thumbnail {
  /** source url of thumbnail (only supports http(s) and attachments) */
  char *url;
  /** a proxied url of the thumbnail */

  char *proxy_url;

  /** height of thumbnail */

  int height;

  /** width of thumbnail */

  int width;
};
struct discord_embed_video {
  /** source url of video */

  char *url;

  /** a proxied url of the video */

  char *proxy_url;

  /** height of video */

  int height;

  /** width of video */

  int width;
};
struct discord_embed_image {
  /** source url of image (only supports http(s) and attachments) */
  char *url;
  /** a proxied url of the image */

  char *proxy_url;

  /** height of image */

  int height;

  /** width of image */

  int width;
};
struct discord_embed_provider {
  /** name of provider */

  char *name;

  /** url of provider */

  char *url;
};
struct discord_embed_author {
  /** name of author */
  char *name;
  /** url of author */

  char *url;

  /** url of author icon (only supports http(s) and attachments) */

  char *icon_url;

  /** a proxied url of author icon */

  char *proxy_icon_url;
};
struct discord_embed_footer {
  /** footer text */
  char *text;
  /** url of footer icon (only supports http(s) and attachments) */

  char *icon_url;

  /** a proxied url of footer icon */

  char *proxy_icon_url;
};
struct discord_embed_field {
  /** name of the field */
  char *name;
  /** value of the field */
  char *value;
  /** whether or not this field should display inline */
  bool Inline;
};
struct discord_embed_fields {
  int size;
  struct discord_embed_field *array;
  int realsize;
};
struct discord_channel_mention {
  /** ID of the channel */
  u64snowflake id;
  /** ID of the guild containing the channel */
  u64snowflake guild_id;
  /** the type of the channel */
  enum discord_channel_types type;
  /** the name of the channel */
  char *name;
};
struct discord_allowed_mention {
  /** An array of allowed mention tpes to parse from the content */
  struct strings *parse;
  /** Array of role_ids to mention (Max size of 100) */
  struct snowflakes *roles;
  /** Array of user_ids to mention (Max size of 100) */
  struct snowflakes *users;
  /** For replies, whether to mention the author of the message being
       replied to (default false) */
  bool replied_user;
};
struct discord_thread_response_body {
  /** the archived threads */
  struct discord_channels *threads;
  /** a thread member object for each returned thread the current user has
       joined */
  struct discord_thread_members *members;
  /** whether there are potentially additional threads that could be returned
       on a subsequent call */
  bool has_more;
};
struct discord_modify_channel {
  /** 1-100 character channel name */
  char *name;
  /** the type of channel; only conversion between text and news is
       supported and only in guilds with the `NEWS` feature */
  enum discord_channel_types type;
  /** the position of the channel in the left-hand listing */

  int position;

  /** 0-1024 character channel topic */
  char *topic;
  /** whether the channel is nsfw */
  bool nsfw;
  /** amount of seconds a user has to wait before sending another message
       (0-21600); bots, as well as users with the permission
       `MANAGE_MESSAGES` or `MANAGE_CHANNEL`, are unaffected */

  int rate_limit_per_user;

  /** the user limit of the voice channel; 0 refers to no limit, 1 to 99
       refers to a user limit */

  int user_limit;

  /** channel or category-specific permissions */

  struct discord_overwrites *permission_overwrites;

  /** ID of the new parent category for a channel */

  u64snowflake parent_id;

  /** channel voice region id, automatic when set to NULL */
  char *rtc_region;
  /** the camera video quality mode of the voice channel */

  int video_quality_mode;

  /** the default duration that the clients use (not the API) for newly
       created threads in the channel, in minutes, to automatically archive
       the thread after recent activity */

  int default_auto_archive_duration;

  /** whether the thread is archived */
  bool archived;
  /** duration in minutes to automatically arhived the thread after recent
       activity, can be set to: 60, 1440, 4320, 10080 */

  int auto_archive_duration;

  /** whether the thread is locked; when a thread is locked, only users with
       `MANAGE_THREADS` can unarchive it */
  bool locked;
  /** whether non-moderators can add other non-moderators to a thread; only
       available on private threads */
  bool invitable;
};
struct discord_get_channel_messages {
  /** get messages around this message ID */

  u64snowflake around;

  /** get messages before this message ID */

  u64snowflake before;

  /** get messages after this message ID */

  u64snowflake after;

  /** max number of messages to return (1-100) */

  int limit;
};
struct discord_create_message {
  /** the message contents (up to 2000 characters) */
  char *content;
  /** true if this is a TTS message */
  bool tts;
  /** embedded `rich` content (up to 6000 characters) */
  struct discord_embeds *embeds;
  /** allowed mentions for the message */

  struct discord_allowed_mention *allowed_mentions;

  /** include to make your message a reply */

  struct discord_message_reference *message_reference;

  /** the components to include with the message */

  struct discord_components *components;

  /** IDs of up to 3 stickers in the server to send in the message */

  struct snowflakes *sticker_ids;

  /** attachment objects with filename and description */

  struct discord_attachments *attachments;

  /** message flags combined as a bitfield (only `SUPPRESS_EMBEDS` can be
       set */

  enum discord_message_flags flags;
};
struct discord_get_reactions {
  /** get users after this user ID */

  u64snowflake after;

  /** max number of users to return (1-100) */

  int limit;
};
struct discord_edit_message {
  /** the message contents (up to 2000 characters) */
  char *content;
  /** embedded `rich` content (up to 6000 characters) */
  struct discord_embeds *embeds;
  /** message flags combined as a bitfield (only `SUPPRESS_EMBEDS` can be
       set */

  enum discord_message_flags flags;

  /** allowed mentions for the message */

  struct discord_allowed_mention *allowed_mentions;

  /** the components to include with the message */

  struct discord_components *components;

  /** attachment objects with filename and description */

  struct discord_attachments *attachments;
};
struct discord_bulk_delete_messages {
  /** an array of message ids to delete (2-100) */
  struct snowflakes *messages;
};
struct discord_edit_channel_permissions {
  /** the bitwise value of all allowed permissions (default \0\) */

  u64bitmask allow;

  /** the bitwise value of all disallowed permissions (default \0\) */

  u64bitmask deny;

  /** 0 for a role or 1 for a member */
  int type;
};
struct discord_create_channel_invite {
  /** duration of invite in seconds before expiry, or 0 for never. between
       0 and 604800 (7 days) */

  int max_age;

  /** max number of uses or 0 for unlimited. betwee 0 and 100 */

  int max_uses;

  /** whether this invite only grants temporary membership */

  bool temporary;

  /** if true, don't true to reuse a similar invite (useful for creating
       many unique one time use invites) */

  bool unique;

  /** the type of target for this voice channel invite */

  enum discord_invite_target_types target_type;

  /** the id of the user whose stream to display for this invite, required
       if `target_type` is 1, the user must be streaming in the channel */

  u64snowflake target_user_id;

  /** the id of the embedded application to open for this invite, required
       if `target_type` is 2, the application must have the `EMBEDDED` flag */

  u64snowflake target_application_id;
};
struct discord_follow_news_channel {
  /** id of target channel */

  u64snowflake webhook_channel_id;
};
struct discord_group_dm_add_recipient {
  /** access token of a user that has granted your app the `gdm.join` scope */
  char *access_token;
  /** nickname of the user being added */
  char *nick;
};
struct discord_start_thread_with_message {
  /** 1-100 character channel name */
  char *name;
  /** duration in minutes to automatically archive the thread after recent
       activity, can be set to: 60, 1440, 4320, 10080 */

  int auto_archive_duration;

  /** amount of seconds a user has to wait before sending another message
       (0-21600) */

  int rate_limit_per_user;
};
struct discord_start_thread_without_message {
  /** 1-100 character channel name */
  char *name;
  /** duration in minutes to automatically archive the thread after recent
       activity, can be set to: 60, 1440, 4320, 10080 */

  int auto_archive_duration;

  /** the type of thread to create */
  enum discord_channel_types type;
  /** whether non-moderators can add other non-moderators to a thread; only
       available when creating a private thread */
  bool invitable;
  /** amount of seconds a user has to wait before sending another message
       (0-21600) */

  int rate_limit_per_user;
};
struct discord_list_active_threads {
  /** the active threads */

  struct discord_channels *threads;

  /** a thread member object for each returned thread the current user has
       joined */

  struct discord_thread_members *members;

  /** whether there are potentially additional threads that could be returned
       on a subsequent call */
  bool has_more;
};
struct discord_emoji {
  /** emoji ID */
  u64snowflake id;
  /** emoji name */
  char *name;
  /** roles allowed to use this emoji */

  struct discord_roles *roles;

  /** user that created this emoji */

  struct discord_user *user;

  /** whether this emoji must be wrapped in colons */
  bool require_colons;
  /** whether this emoji is managed */
  bool managed;
  /** whether this emoji is animated */
  bool animated;
  /** whether this emoji can be used, may be false due to loss of Server
       Boosts */
  bool available;
};
struct discord_emojis {
  int size;
  struct discord_emoji *array;
  int realsize;
};
struct discord_create_guild_emoji {
  /** name of the emoji */
  char *name;
  /** the 128x128 emoji image */
  char *image;
  /** roles allowed to use this emoji */

  struct snowflakes *roles;
};
struct discord_modify_guild_emoji {
  /** name of the emoji */
  char *name;
  /** the 128x128 emoji image */
  char *image;
  /** roles allowed to use this emoji */

  struct snowflakes *roles;
};
enum discord_message_notification_level {
  /** members will receive notifications for all messages by default */
  DISCORD_MESSAGE_NOTIFICATION_ALL_MESSAGES = 0,
  /** members will receive notifications only for messages that `@mention`
       them by default */
  DISCORD_MESSAGE_NOTIFICATION_ONLY_MESSAGES = 1
};
enum discord_explicit_content_filter_level {
  /** media content will not be scanned */
  DISCORD_EXPLICIT_CONTENT_DISABLED = 0,
  /** media content sent by members without roles will be scanned */
  DISCORD_EXPLICIT_CONTENT_MEMBERS_WITHOUT_ROLES = 1,
  /** media content sent by all members will be scanned */
  DISCORD_MESSAGE_NOTIFICATION_ALL_MEMBERS = 2
};
enum discord_mfa_level {
  /** guild has no MFA/2FA requirement for moderation actions */
  DISCORD_MFA_NONE = 0,
  /** guild has a 2FA requirement for moderation actions */
  DISCORD_MFA_ELEVATED = 1
};
enum discord_verification_level {
  /** unrestricted */
  DISCORD_VERIFICATION_NONE = 0,
  /** must have verified email on account */
  DISCORD_VERIFICATION_LOW = 1,
  /** must be registered on Discord for longer than 5 minutes */
  DISCORD_VERIFICATION_MEDIUM = 2,
  /** must be a member of the server for longer than 10 minutes */
  DISCORD_VERIFICATION_HIGH = 3,
  /** must have a verified phone number */
  DISCORD_VERIFICATION_VERY_HIGH = 4
};
enum discord_guild_nsfw_level {
  DISCORD_GUILD_NSFW_DEFAULT = 0,
  DISCORD_GUILD_NSFW_EXPLICIT = 1,
  DISCORD_GUILD_NSFW_SAFE = 2,
  DISCORD_GUILD_NSFW_AGE_RESTRICTED = 3
};
enum discord_premium_tier {
  /** guild has not unlocked any Server Boost perks */
  DISCORD_PREMIUM_TIER_NONE = 0,
  /** guild has unlocked Server Boost level 1 perks */
  DISCORD_PREMIUM_TIER_1 = 1,
  /** guild has unlocked Server Boost level 2 perks */
  DISCORD_PREMIUM_TIER_2 = 2,
  /** guild has unlocked Server Boost level 3 perks */
  DISCORD_PREMIUM_TIER_3 = 3
};
enum discord_system_channel_flags {
  /** suppress member join notifications */
  DISCORD_SYSTEM_SUPPRESS_JOIN_NOTIFICATIONS = 1 << 0,
  /** suppress server boost notifications */
  DISCORD_SYSTEM_SUPPRESS_PREMIUM_NOTIFICATIONS = 1 << 1,
  /** suppress server setup tips */
  DISCORD_SYSTEM_SUPPRESS_GUILD_REMINDER_NOTIFICATIONS = 1 << 2,
  /** hide member join sticker reply buttons */
  DISCORD_SYSTEM_SUPPRESS_JOIN_NOTIFICATION_REPLIES = 1 << 3
};
enum discord_integration_expire_behaviors {
  DISCORD_INTEGRATION_REMOVE_ROLE = 0,
  DISCORD_INTEGRATION_KICK = 1
};
struct discord_guild {
  /** guild id */
  u64snowflake id;
  /** guild name (2-100 characters, excluding trailing and leading
       whitespace */
  char *name;
  /** icon hash */
  char *icon;
  /** icon hash, returned when in the template object */

  char *icon_hash;

  /** splash hash */
  char *splash;
  /** discovery splash hash, only present for `DISCOVERABLE` guilds */
  char *discovery_splash;
  /** true if the user is the owner of the guild */
  bool owner;
  /** id of owner */
  u64snowflake owner_id;
  /** total permissions for the user in the guild (exclues overwrites) */

  char *permissions;

  /** id of afk channel */
  u64snowflake afk_channel_id;
  /** afk timeout in seconds */
  int afk_timeout;
  /** true if the server widget is enabled */
  bool widget_enabled;
  /** the channel id the widget will generate an invite to, or NULL if set
       to no invite */
  u64snowflake widget_channel_id;
  /** verification level required for the guild */
  enum discord_verification_level verification_level;
  /** default message notifications level */
  enum discord_message_notification_level default_message_notifications;
  /** explicit content filter level */
  enum discord_explicit_content_filter_level explicit_content_filter;
  /** roles in the guilds */
  struct discord_roles *roles;
  /** custom guild emojis */
  struct discord_emojis *emojis;
  /** enabled guild features */
  struct strings *features;
  /** required MFA level for the guild */
  enum discord_mfa_level mfa_level;
  /** application id of the guild creator if it is bot-created */
  u64snowflake application_id;
  /** the id of the channel where guild notices such as welcome messages and
       boost events are posted */
  u64snowflake system_channel_id;
  /** system channel flags */
  enum discord_system_channel_flags system_channel_flags;
  /** the id of the channel where Community guilds can display rules and/or
       guidelines */
  u64snowflake rules_channel_id;
  /** when this guild was joined at */

  u64unix_ms joined_at;

  /** true if this is considered a large guild */
  bool large;
  /** true if this guild is unavailable due to an outage */
  bool unavailable;
  /** total number of members in this guild */
  int member_count;
  /** states of members currently in voice channels; lacks `guild_id` */

  struct discord_voice_states *voice_states;

  /** users in the guild */

  struct discord_guild_members *members;

  /** channels in the guild */

  struct discord_channels *channels;

  /** all active threads in the guild that current user has permission to
       view */

  struct discord_channels *threads;

  /** presences of the members in the guild, will only include non-offline
       members if the size is greater than `large threshold` */

  struct discord_presence_updates *presences;

  /** the maximum number of presences for the guild (null is always
       returned, apart from the largest of guilds) */

  int max_presences;

  /** the maximum number of members for the guild */

  int max_members;

  /** the vanity url code for the guild */
  char *vanity_url_code;
  /** the description of a Community guild */
  char *description;
  /** banner hash */
  char *banner;
  /** premium tier (Server Boost level) */
  enum discord_premium_tier premium_tier;
  /** the number of boosts this guild currently has */
  int premium_subscription_count;
  /** the preferred locale of a Community guild; used in server discovery and
       notices from Discord, and sent in interactions; defaults to \en-US\ */
  char *preferred_locale;
  /** the id of the channel where admins and moderators of Community guilds
       receive notices from Discord */
  u64snowflake public_updates_channel_id;
  /** the maximum amount of users in a video channel */

  int max_video_channel_users;

  /** approximate number of members in this guild */

  int approximate_member_count;

  /** approximate number of non-offline members in this guild */

  int approximate_presence_count;

  /** the welcome screen of a Community guild, shown to new members, returned
       in an invite's guild object */

  struct discord_welcome_screen *welcome_screen;

  /** guild NSFW level */
  enum discord_guild_nsfw_level nsfw_level;
  /** stage instances in the guild */

  struct discord_stage_instances *stage_instances;

  /** custom guild stickers */

  struct discord_stickers *stickers;

  /** the scheduled events in the guilds */

  struct discord_guild_scheduled_events *guild_scheduled_events;

  /** whether the guild has the boost progress bar enabled */
  bool premium_progress_bar_enabled;
};
struct discord_guilds {
  int size;
  struct discord_guild *array;
  int realsize;
};
struct discord_guild_preview {
  /** guild id */
  u64snowflake id;
  /** guild name (2-100 characters) */
  char *name;
  /** icon hash */
  char *icon;
  /** splash hash */
  char *splash;
  /** discovery splash hash */
  char *discovery_splash;
  /** custom guild emojis */
  struct discord_emojis *emojis;
  /** enabled guild features */
  struct strings *features;
  /** approximate number of members in this guild */
  int approximate_member_count;
  /** approximate number of online members in this guild */
  int approximate_presence_count;
  /** the description for the guid, if the guild is discoverable */
  char *description;
  /** custom guild stickers */
  struct discord_stickers *stickers;
};
struct discord_guild_widget_setting {
  /** whether the widget is enabled */
  bool enabled;
  /** the widget channel ID */
  u64snowflake channel_id;
};
struct discord_get_guild_widget {
  /** guild id */
  u64snowflake id;
  /** guild name (2-100 characters) */
  char *name;
  /** instant invite for the guilds specified widget invite channel */
  char *instant_invite;
  /** voice and stage channels which are accessible by `@everyone` */
  struct discord_channels *channels;
  /** special widget user objects that includes users presence (limit 100) */
  struct discord_users *members;
  /** number of online members in this guild */
  int presence_count;
};
struct discord_guild_member {
  /** the user this guild member represents */

  struct discord_user *user;

  /** this user's guild nickname */

  char *nick;

  /** the member's guild avatar hash */

  char *avatar;

  /** array of role object IDs */
  struct snowflakes *roles;
  /** when the user joined the guild */
  u64unix_ms joined_at;
  /** when the user started boosting the guild */

  u64unix_ms premium_since;

  /** whether the user is deafened in voice channels */
  bool deaf;
  /** whether the user is muted in voice channels */
  bool muted;
  /** whether the user has not yet passed the guild's Membership Screening
       requirements */
  bool pending;
  /** total permission of the member in the channel, including overwrites,
       returned when in the interaction object */

  char *permissions;

  /** when the user's timeout will expire and the user will be able to
       communicate in the guild again, null or a time in the past if the
       user is not timed out */
  u64unix_ms communication_disabled_until;
};
struct discord_guild_members {
  int size;
  struct discord_guild_member *array;
  int realsize;
};
struct discord_integration {
  /** integration id */
  u64snowflake id;
  /** integration name */
  char *name;
  /** integration type (twitch, youtube, or discord) */
  char *type;
  /** is this integration enabled */
  bool enabled;
  /** is this integration syncing */
  bool syncing;
  /** ID that this integration uses for \subscribers\ */
  u64snowflake role_id;
  /** whether emoticons should be synced for this integration (twitch only
       currently) */
  bool enable_emoticons;
  /** the behavior of expiring subscribers */
  enum discord_integration_expire_behaviors expire_behavior;
  /** the grace period (in days) before expiring subscribers */
  int expire_grace_period;
  /** user for this integration */
  struct discord_user *user;
  /** integration account information */
  struct discord_integration_account *account;
  /** when this integration was last synced */
  u64unix_ms synced_at;
  /** how many subscribers this integration has */
  int subscriber_count;
  /** has this integration been revoked */
  bool revoked;
  /** the bot/OAuth2 application for discord integrations */
  struct discord_integration_application *application;
};
struct discord_integrations {
  int size;
  struct discord_integration *array;
  int realsize;
};
struct discord_integration_account {
  /** id of the account */
  char *id;
  /** name of the account */
  char *name;
};
struct discord_integration_application {
  /** the id of the app */
  u64snowflake id;
  /** the name of the app */
  char *name;
  /** the icon hash of the app */
  char *icon;
  /** the description of the app */
  char *description;
  /** the summary of the app */
  char *summary;
  /** the bot associated with this application */

  struct discord_user *bot;
};
struct discord_ban {
  /** the reason for the ban */
  char *reason;
  /** the banned user */
  struct discord_user *user;
};
struct discord_bans {
  int size;
  struct discord_ban *array;
  int realsize;
};
struct discord_welcome_screen {
  /** the server description shown in the welcome screen */
  char *description;
  /** the channels shown in the welcome screen, up to 5 */

  struct discord_welcome_screen_channels *welcome_channels;
};
struct discord_welcome_screen_channel {
  /** the channel's id */
  u64snowflake channel_id;
  /** the description shown for the channel */
  char *description;
  /** the emoji id, if the emoji is custom */
  u64snowflake emoji_id;
  /** the emoji name if custom, the unicode character if standard, or NULL if
       no emoji is set */
  char *emoji_name;
};
struct discord_welcome_screen_channels {
  int size;
  struct discord_welcome_screen_channel *array;
  int realsize;
};
struct discord_create_guild {
  /** name of the guild (2-100 charaters) */
  char *name;
  /** voice region ID @deprecated deprecated field */

  char *region;

  /** base64 1024x1024 png/jpeg/gif image for the guild icon (can be
       animated gif when the server has the `ANIMATED_ICON` feature) */

  char *icon;

  /** verification level */
  enum discord_verification_level verification_level;
  /** default message notification level */
  enum discord_message_notification_level default_message_notifications;
  /** explicit content filter level */
  enum discord_explicit_content_filter_level explicit_content_filter;
  /** new guild roles */

  struct discord_roles *roles;

  /** new guild's channels */

  struct discord_channels *channels;

  /** ID for afk channel */

  u64snowflake afk_channel_id;

  /** afk timeout in seconds */
  int afk_timeout;
  /** the ID of the channel when guild notices such as welcome messages and
       boost events are posted */
  u64snowflake system_channel_id;
  /** system channel flags */
  enum discord_system_channel_flags system_channel_flags;
};
struct discord_modify_guild {
  /** guild name */
  char *name;
  /** verification level */
  enum discord_verification_level verification_level;
  /** default message notification level */
  enum discord_message_notification_level default_message_notifications;
  /** explicit content filter level */
  enum discord_explicit_content_filter_level explicit_content_filter;
  /** ID for afk channel */
  u64snowflake afk_channel_id;
  /** afk timeout in seconds */
  int afk_timeout;
  /** base64 1024x1024 png/jpeg/gif image for the guild icon (can be
       animated gif when the server has the `ANIMATED_ICON` feature) */
  char *icon;
  /** user ID to transfer guild ownership to (must be owner) */
  u64snowflake owner_id;
  /** base64 1024x1024 png/jpeg/gif image for the guild splash (can be
       animated gif when the server has the `INVITE_SPLASH` feature) */
  char *splash;
  /** base64 1024x1024 png/jpeg/gif image for the guild discovery splash
       (can be animated gif when the server has the `DISCOVERABLE` feature) */
  char *discovery_splash;
  /** base64 1024x1024 png/jpeg/gif image for the guild banner (can be
       animated gif when the server has the `BANNER` feature) */
  char *banner;
  /** the ID of the channel when guild notices such as welcome messages and
       boost events are posted */
  u64snowflake system_channel_id;
  /** system channel flags */
  enum discord_system_channel_flags system_channel_flags;
  /** the ID of the channel where Community guilds display rules and/or
       guidelines */
  u64snowflake rules_channel_id;
  /** the ID of the channel where admins and moderators of Community guild
       receive notices from Discord */
  u64snowflake public_updates_channel_id;
  /** the preferred locale of a Community guild used in a server discovery
       and notices from Discord; defaults to \en-US\ */
  char *preferred_locale;
  /** enabled guild features */
  struct strings *features;
  /** the description for the guild, if the guild is discoverable */
  char *description;
  /** whether the guild's boost progress bar should be enabled */
  bool premium_progress_bar_enabled;
};
struct discord_create_guild_channel {
  /** channel name (1-100 characters) */
  char *name;
  /** the type of channel */
  enum discord_channel_types type;
  /** channel topic (0-1024 characters) */
  char *topic;
  /** the bitrate (in bits) of the voice channel (voice only) */

  int bitrate;

  /** the user limit of the voice channel (voice only) */

  int user_limit;

  /** amount of seconds a user has to wait before sending another message
       (0-21600); bots, as well as users with the permission
       `MANAGE_MESSAGES` or `MANAGE_CHANNEL`, are unaffected */
  int rate_limit_per_user;
  /** sorting position of the channel */
  int position;
  /** the channel's permission overwrites */
  struct discord_overwrites *permission_overwrites;
  /** ID of the parent category for a channel */

  u64snowflake parent_id;

  /** whether the channel is nsfw */
  bool nsfw;
};
struct discord_modify_guild_channel_position {
  /** channel ID */
  u64snowflake id;
  /** sorting position of the channel */

  int position;

  /** syncs the permission overwrites with the new parent, if moving to a new
       category */
  bool lock_category;
  /** the new parent ID for the channel that is moved */

  u64snowflake parent_id;
};
struct discord_modify_guild_channel_positions {
  int size;
  struct discord_modify_guild_channel_position *array;
  int realsize;
};
struct discord_list_active_guild_threads {
  /** the active threads */
  struct discord_channels *threads;
  /** a thread member object for each returned thread the current user has
       joined */
  struct discord_thread_members *members;
};
struct discord_list_guild_members {
  /** max number of members to return (1-1000) */
  int limit;
  /** the highest user ID in the previous page */
  u64snowflake after;
};
struct discord_search_guild_members {
  /** query string to match username(s) and nickname(s) against */
  char *query;
  /** max number of members to return (1-1000) */
  int limit;
};
struct discord_add_guild_member {
  /** an oauth2 access token granted with the `guild.join` to the bot's
       application for the user you want to add in the guild */
  char *access_token;
  /** value to set user's nickname to */
  char *nick;
  /** array of role IDs the member is assigned */
  struct snowflakes *roles;
  /** whether the user is muted in voice channels */
  bool mute;
  /** whether the user is deafened in voice channels */
  bool deaf;
};
struct discord_modify_guild_member {
  /** value to set user's nickname to */
  char *nick;
  /** array of role IDs the member is assigned */
  struct snowflakes *roles;
  /** whether the user is muted in voice channels. will return a
       @ref CCORD_HTTP_ERROR (400) if the user is not in a voice channel */
  bool mute;
  /** whether the user is deafened in voice channels. will return a
       @ref CCORD_HTTP_ERROR (400) if the user is not in a voice channel */
  bool deaf;
  /** ID of channel to move user to (if they are connect to voice) */
  u64snowflake channel_id;
  /** when the user's timeout will expire and the user will be able to
       communicate in the guild again (up to 28 days in the future), set
       to NULL to remove timeout. WIll throw a @ref CCORD_HTTP_ERROR (403)
       error if the user has the `ADMINISTRATOR` permission or is the owner
       of the guild */

  u64unix_ms communication_disabled_until;
};
struct discord_modify_current_member {
  /** value to set user's nickname to */

  char *nick;
};
struct discord_modify_current_user_nick {
  /** value to set user's nickname to */

  char *nick;
};
struct discord_create_guild_ban {
  /** number of days to delete messages for (0-7) */

  int delete_message_days;

  /** reason for the ban @deprecated deprecated field */

  char *reason;
};
struct discord_create_guild_role {
  /** name of the role */
  char *name;
  /** `@everyone` permissions in guild */
  u64snowflake permissions;
  /** RGB color value */
  int color;
  /** whether the role should be displayed separately in the sidebar */
  bool hoist;
  /** the role's icon image (if the guild has the `ROLE_ICONS` feature) */
  char *icon;
  /** the role's unicode emoji as a standard emoji (if the guild has the
       `ROLE_ICONS` feature) */
  char *unicode_emoji;
  /** whether the role should be mentionable */
  bool mentionable;
};
struct discord_modify_guild_role_position {
  /** role */
  u64snowflake id;
  /** sorting position of the role */

  int position;
};
struct discord_modify_guild_role_positions {
  int size;
  struct discord_modify_guild_role_position *array;
  int realsize;
};
struct discord_modify_guild_role {
  /** name of the role */
  char *name;
  /** bitwise value of the enabled/disabled permissions */
  u64snowflake permissions;
  /** RGB color value */
  int color;
  /** whether the role should be displayed separately in the sidebar */
  bool hoist;
  /** the role's icon image (if the guild has the `ROLE_ICONS` feature) */
  char *icon;
  /** the role's unicode emoji as a standard emoji (if the guild has the
       `ROLE_ICONS` feature) */
  char *unicode_emoji;
  /** whether the role should be mentionable */
  bool mentionable;
};
struct discord_get_guild_prune_count {
  /** number of days to count prune for (1-30) */

  int count;

  /** role(s) to include */
  struct snowflakes *include_roles;
};
struct discord_begin_guild_prune {
  /** number of days to prune */

  int days;

  /** whether 'pruned' is returned, discouraged for large guilds */
  bool compute_prune_count;
  /** role(s) to include */
  struct snowflakes *include_roles;
  /** reason for the prune @deprecated deprecated field */

  char *reason;
};
struct discord_get_guild_widget_image {
  /** style of the widget image returned
       @see
     https://discord.com/developers/docs/resources/guild#membership-screening-object-widget-style-options
     */

  char *style;
};
struct discord_modify_guild_welcome_screen {
  /** whether the welcome screen is enabled */
  bool enabled;
  /** channels linked in the welcome screen and their display options */
  struct discord_welcome_screen_channels *welcome_channels;
  /** the server description to show in the welcome screen */

  char *description;
};
struct discord_modify_current_user_voice_state {
  /** the ID of the channel the user is currently in */
  u64snowflake channel_id;
  /** toggles the user's suppress state */
  bool suppress;
  /** set the user's request to speak */

  u64unix_ms request_to_speak_timestamp;
};
struct discord_modify_user_voice_state {
  /** the ID of the channel the user is currently in */
  u64snowflake channel_id;
  /** toggles the user's suppress state */
  bool suppress;
};
enum discord_guild_scheduled_event_privacy_level {
  /** the scheduled event is only accessible to guild members */
  DISCORD_GUILD_SCHEDULED_EVENT_GUILD_ONLY = 2
};
enum discord_guild_scheduled_event_entity_types {
  DISCORD_GUILD_SCHEDULED_EVENT_ENTITY_STAGE_INSTANCE = 1,
  DISCORD_GUILD_SCHEDULED_EVENT_ENTITY_VOICE = 2,
  DISCORD_GUILD_SCHEDULED_EVENT_ENTITY_EXTERNAL = 3
};
enum discord_guild_scheduled_event_status {
  DISCORD_GUILD_SCHEDULED_EVENT_SCHEDULED = 1,
  DISCORD_GUILD_SCHEDULED_EVENT_ACTIVE = 2,
  DISCORD_GUILD_SCHEDULED_EVENT_COMPLETED = 3,
  DISCORD_GUILD_SCHEDULED_EVENT_CANCELED = 4
};
struct discord_guild_scheduled_event {
  /** the ID of the scheduled event */
  u64snowflake id;
  /** the guild ID which the scheduled event belongs to */
  u64snowflake guild_id;
  /** the channel ID in which the scheduled event will be hosted, or `NULL`
       if `entity_type` is @ref DISCORD_SCHEDULED_ENTITY_EXTERNAL */
  u64snowflake channel_id;
  /** the ID of the user that created the scheduled event */
  u64snowflake creator_id;
  /** the name of the scheduled event (1-100 characters) */
  char *name;
  /** the description of the scheduled event (1-1000 characters) */
  char *description;
  /** the time the scheduled event will start */
  u64unix_ms scheduled_start_time;
  /** the time the scheduled event will end, required if `entity_type` is
       @ref DISCORD_SCHEDULED_ENTITY_EXTERNAL */
  u64unix_ms scheduled_end_time;
  /** the privacy level of the scheduled event */

  enum discord_guild_scheduled_event_privacy_level privacy_level;

  /** the status of the scheduled event */

  enum discord_guild_scheduled_event_status status;

  /** the type of scheduled event */

  enum discord_guild_scheduled_event_entity_types entity_type;

  /** the ID of an entity associated with a guild scheduled event */
  u64snowflake entity_id;
  /** additional metadata for the guild scheduled event */

  struct discord_guild_scheduled_event_entity_metadata *entity_metadata;

  /** the user that created the scheduled event */

  struct discord_user *creator;

  /** the number of users subscribed to the scheduled event */
  int user_count;
  /** the cover image hashof the scheduled event */
  char *image;
};
struct discord_guild_scheduled_events {
  int size;
  struct discord_guild_scheduled_event *array;
  int realsize;
};
struct discord_guild_scheduled_event_entity_metadata {
  /** location of the event (1-100 characters) */

  char *location;
};
struct discord_guild_scheduled_event_user {
  /** the scheduled event ID which the user subscribed to */
  u64snowflake guild_scheduled_event_id;
  /** user which subscribed to an event */

  struct discord_user *user;

  /** guild member data for this user for the guild which this event belongs
       to, if any */

  struct discord_guild_member *member;
};
struct discord_list_scheduled_events_for_guild {
  /** include number of users subscribed to each event */
  bool with_user_count;
};
struct discord_create_guild_scheduled_event {
  /** the channel ID of the scheduled event */

  u64snowflake channel_id;

  /** the entity metadata of the scheduled event */

  struct discord_guild_scheduled_event_entity_metadata *entity_metadata;

  /** the name of the scheduled event */
  char *name;
  /** the time the scheduled event will start */

  u64unix_ms scheduled_start_time;

  /** the time the scheduled event will end */

  u64unix_ms scheduled_end_time;

  /** the description of the scheduled event */

  char *description;

  /** the entity type of the scheduled event */

  enum discord_guild_scheduled_event_entity_types entity_type;

  /** the cover image of the scheduled event */

  char *image;
};
struct discord_get_guild_scheduled_event {
  /** include number of users subscribed to each event */
  bool with_user_count;
};
struct discord_modify_guild_scheduled_event {
  /** the channel ID of the scheduled event */

  u64snowflake channel_id;

  /** the entity metadata of the scheduled event */

  struct discord_guild_scheduled_event_entity_metadata *entity_metadata;

  /** the name of the scheduled event */
  char *name;
  /** the time the scheduled event will start */

  u64unix_ms scheduled_start_time;

  /** the time the scheduled event will end */

  u64unix_ms scheduled_end_time;

  /** the description of the scheduled event */

  char *description;

  /** the entity type of the scheduled event */

  enum discord_guild_scheduled_event_entity_types entity_type;

  /** the status of the scheduled event */

  enum discord_guild_scheduled_event_status status;

  /** the cover image of the scheduled event */

  char *image;
};
struct discord_get_guild_scheduled_event_users {
  /** number of users to return (up to maximum of 100) */
  int limit;
  /** include guild member data if exists */
  bool with_member;
  /** consider only users before given user ID */

  u64snowflake before;

  /** consider only users after given user ID */

  u64snowflake after;
};
struct discord_guild_template {
  /** the template code (unique ID) */
  char *code;
  /** template name */
  char *name;
  /** the description for the template */
  char *description;
  /** number of times this template has been used */
  int usage_count;
  /** the ID of the user who created the template */
  u64snowflake creator_id;
  /** the user who created the template */
  struct discord_user *creator;
  /** when this template was created */
  u64unix_ms created_at;
  /** when this template was last synced to the source guild */
  u64unix_ms updated_at;
  /** the ID of the guild this template is based on */
  u64snowflake source_guild_id;
  /** the guild snapshot this template contains */
  struct discord_guild *serialized_source_guild;
  /** whether the template has unsynced changes */
  bool is_dirty;
};
struct discord_create_guild_from_guild_template {
  /** name of the guild (2-100 characters) */
  char *name;
  /** base64 128x128 image for the guild icon */

  char *icon;
};
struct discord_create_guild_template {
  /** name of the template (1-100 characters) */
  char *name;
  /** description for the template (0-120 characters) */

  char *description;
};
struct discord_modify_guild_template {
  /** name of the template (1-100 characters) */

  char *name;

  /** description for the template (0-120 characters) */

  char *description;
};
enum discord_privacy_level {
  /** the stage instance is visible publicly @deprecated deprecated value */
  DISCORD_PRIVACY_PUBLIC = 1,
  /** the stage instance is visible to only guild members */
  DISCORD_PRIVACY_GUILD_ONLY = 2
};
struct discord_stage_instance {
  /** the ID of this stage instance */
  u64snowflake id;
  /** the guild ID of the associated stage channel */
  u64snowflake guild_id;
  /** the ID of the associated stage channel */
  u64snowflake channel_id;
  /** the topic of the Stage instance (1-120 characters) */
  char *topic;
  /** the privacy level of the stage instance */

  enum discord_privacy_level privacy_level;

  /** whether or not stage discovery is disabled @deprecated deprecated field */
  bool discoverable_disabled;
};
struct discord_stage_instances {
  int size;
  struct discord_stage_instance *array;
  int realsize;
};
struct discord_create_stage_instance {
  /** the ID of the stage channel */
  u64snowflake channel_id;
  /** the topic of the Stage instance (1-120 characters) */
  char *topic;
  /** the privacy level of the stage instance */

  enum discord_privacy_level privacy_level;
};
struct discord_modify_stage_instance {
  /** the topic of the Stage instance (1-120 characters) */
  char *topic;
  /** the privacy level of the stage instance */

  enum discord_privacy_level privacy_level;
};
enum discord_sticker_types {
  /** an official sticker in a pack, part of Nitro or in a removed
       purchasable pack */
  DISCORD_STICKER_STANDARD = 1,
  /** a sticker uploaded to a Boosted guild for the guild's members */
  DISCORD_STICKER_GUILD = 2
};
enum discord_sticker_format_types {
  DISCORD_STICKER_FORMAT_PNG = 1,
  DISCORD_STICKER_FORMAT_APNG = 2,
  DISCORD_STICKER_FORMAT_LOTTIE = 3
};
struct discord_sticker {
  /** ID of the sticker */
  u64snowflake id;
  /** for standard stickers, ID of the pack the sticker is from */

  u64snowflake pack_id;

  /** name of the sticker */
  char *name;
  /** description of the sticker */
  char *description;
  /** autocomplete/suggestion tags for the sticker (max 200 characters) */
  char *tags;
  /** type of sticker */

  enum discord_sticker_types type;

  /** type of sticker format */

  enum discord_sticker_format_types format_type;

  /** whether this guild sticker can be used, may be false due to loss of
       Server Boosts */
  bool available;
  /** ID of the guild that owns this sticker */

  u64snowflake guild_id;

  /** the user that uploaded the guild sticker */

  struct discord_user *user;

  /** the standard sticker's sort order within its pack */
  int sort_value;
};
struct discord_stickers {
  int size;
  struct discord_sticker *array;
  int realsize;
};
struct discord_sticker_item {
  /** ID of the sticker */
  u64snowflake id;
  /** name of the sticker */
  char *name;
  /** type of sticker format */

  enum discord_sticker_format_types format_type;
};
struct discord_sticker_items {
  int size;
  struct discord_sticker_item *array;
  int realsize;
};
struct discord_sticker_pack {
  /** ID of the sticker */
  u64snowflake id;
  /** the stickers in the pack */

  struct discord_stickers *stickers;

  /** name of the sticker pack */
  char *name;
  /** ID of the pack's SKU */
  u64snowflake sku_id;
  /** ID of a sticker in the pack which is shown as the pack's icon */

  u64snowflake cover_sticker_id;

  /** description of the sticker pack */
  char *description;
  /** ID of the sticker pack's banner image */

  u64snowflake banner_asset_id;
};
struct discord_create_guild_sticker {
  /** name of the sticker (2-30 characters) */
  char *name;
  /** description of the sticker (empty or 2-100 characters) */
  char *description;
  /** autocomplete/suggestion tags for the sticker (max 200 characters) */
  char *tags;
  /** the sticker file to upload, must be a PNG, APNG, or Lottie JSON file
       max 500 KB */
  struct discord_attachment *file;
};
struct discord_modify_guild_sticker {
  /** name of the sticker (2-30 characters) */
  char *name;
  /** description of the sticker (empty or 2-100 characters) */
  char *description;
  /** autocomplete/suggestion tags for the sticker (max 200 characters) */
  char *tags;
};
/** None */
#define DISCORD_USER_NONE 0
/** Discord Employee */
#define DISCORD_USER_STAFF 1 << 0
/** Partnered Server Owner */
#define DISCORD_USER_PARTNER 1 << 1
/** HypeSquad Events Coordinator */
#define DISCORD_USER_HYPESQUAD 1 << 2
/** Bug Hunter Level 1 */
#define DISCORD_USER_BUG_HUNTER_LEVEL_1 1 << 3
/** House Bravery Member */
#define DISCORD_USER_HYPESQUAD_ONLINE_HOUSE_1 1 << 6
/** House Brilliance Member */
#define DISCORD_USER_HYPESQUAD_ONLINE_HOUSE_2 1 << 7
/** House Balance Member */
#define DISCORD_USER_HYPESQUAD_ONLINE_HOUSE_3 1 << 8
/** Early Nitro Supporter */
#define DISCORD_USER_PREMIUM_EARLY_SUPPORTER 1 << 9
/** User is a team */
#define DISCORD_USER_TEAM_PSEUDO_USER 1 << 10
/** Bug Hunter Level 2 */
#define DISCORD_USER_BUG_HUNTER_LEVEL_2 1 << 14
/** Verified Bot */
#define DISCORD_USER_VERIFIED_BOT 1 << 16
/** Early Verified Bot Developer */
#define DISCORD_USER_VERIFIED_DEVELOPER 1 << 17
/** Discord Certified Moderator */
#define DISCORD_USER_CERTIFIED_MODERATOR 1 << 18
/** Bot uses only HTTP interactions and is shownin the online member list */
#define DISCORD_USER_BOT_HTTP_INTERACTIONS 1 << 19
enum discord_premium_types {
  DISCORD_PREMIUM_NONE = 0,
  DISCORD_PREMIUM_NITRO_CLASSIC = 1,
  DISCORD_PREMIUM_NITRO = 2
};
enum discord_visibility_types {
  /** invisible to everyone except the user themselves */
  DISCORD_VISIBILITY_NONE = 0,
  /** visible to everyone */
  DISCORD_VISIBILITY_EVERYONE = 1
};
struct discord_user {
  /** the user's ID */
  u64snowflake id;
  /** the user's username, not unique across the platform */
  char *username;
  /** the user's 4-digit discord tag */
  char *discriminator;
  /** the user's avatar hash */
  char *avatar;
  /** whether the user belong to an OAuth2 application */
  bool bot;
  /** whether the user is an Official Discord System user (part of the
       urgent message system) */
  bool System;
  /** whether the user has two factor enabled on their account */
  bool mfa_enabled;
  /** the user's banner hash */
  char *banner;
  /** the user's banner color encoded as an integer representation of
       hexadecimal color code */
  int accent_color;
  /** the user's chosen language option */
  char *locale;
  /** whether the email on this account has been verified */
  bool verified;
  /** the user's email */
  char *email;
  /** the flags on a user's account */
  u64snowflake flags;
  /** the type of Nitro subscription on a user's account */
  enum discord_premium_types premium_type;
  /** the public flags on a user's account */
  u64snowflake public_flags;
};
struct discord_users {
  int size;
  struct discord_user *array;
  int realsize;
};
struct discord_connection {
  /** ID of the connection account */
  u64snowflake id;
  /** the username of the connection account */
  char *name;
  /** the service of the connection (twitch, youtube) */
  char *type;
  /** whether the connection is revoked */
  bool revoked;
  /** an array of partial server integrations */

  struct discord_integrations *integrations;

  /** whether the connection is verified */
  bool verified;
  /** whether friend sync is enabled for this connection */
  bool friend_sync;
  /** whether activities related to this connection will be shown in presence
       updates */
  bool show_activity;
  /** visibility of this connection */
  enum discord_visibility_types visibility;
};
struct discord_connections {
  int size;
  struct discord_connection *array;
  int realsize;
};
struct discord_modify_current_user {
  /** user's username, if changed may cause the user's discriminator to be
       randomized */

  char *username;

  /** if passed, modified the user's avatar */

  char *avatar;
};
struct discord_get_current_user_guilds {
  /** get guilds before this guild ID */

  u64snowflake before;

  /** get guilds after this guild ID */

  u64snowflake after;

  /** max number of guilds to return (1-200) */

  int limit;
};
struct discord_create_dm {
  /** the recipient to open a DM channel with */

  u64snowflake recipient_id;
};
struct discord_create_group_dm {
  /** access tokens of users that have grantes your app `gdm.join` scope */

  struct snowflakes *access_tokens;

  /** a dictionary of user IDs to their respective nicknames */

  struct strings *nicks;
};
struct discord_voice_state {
  /** the guild ID this voice state is for */
  u64snowflake guild_id;
  /** the channel ID this user is connected to */
  u64snowflake channel_id;
  /** the user ID this voice state is for */
  u64snowflake user_id;
  /** the guild member this voice state is for */
  struct discord_guild_member *member;
  /** the session ID for this voice state */
  char *session_id;
  /** whether this user is deafened by the server */
  bool deaf;
  /** whether this user is muted by the server */
  bool mute;
  /** whether this user is locally deafened */
  bool self_deaf;
  /** whether this user is locally muted */
  bool self_mute;
  /** whether this user is streaming using \Go Live\ */
  bool self_stream;
  /** whether this user is muted by the current user */
  bool self_video;
  /** whether this user is muted by the current user */
  bool suppress;
  /** the time at which the user requested to speak */

  u64unix_ms request_to_speak_timestamp;
};
struct discord_voice_states {
  int size;
  struct discord_voice_state *array;
  int realsize;
};
struct discord_voice_region {
  /** unique ID for the region */
  char *id;
  /** name of the region */
  char *name;
  /** true for a single server that is closest to the current user's client */
  bool optimal;
  /** whether this is a deprecated voice region (avoid switching to these) */
  bool deprecated;
  /** whether this is a custom voice region (used for events/etc) */
  bool custom;
};
struct discord_voice_regions {
  int size;
  struct discord_voice_region *array;
  int realsize;
};
enum discord_webhook_types {
  /** Incoming Webhooks can post messages to channels with a generated token  */
  DISCORD_WEBHOOK_INCOMING = 1,
  /** Channel Follower Webhooks are internal webhooks used with Channel
       Following to post new messages into channels */
  DISCORD_WEBHOOK_CHANNEL_FOLLOWER = 2,
  /** Application webhooks are webhooks used with Interactions */
  DISCORD_WEBHOOK_APPLICATION = 3
};
struct discord_webhook {
  /** the ID of the webhook */
  u64snowflake id;
  /** the type of the webhook */

  enum discord_webhook_types type;

  /** the guild ID this webhook is for, if any */
  u64snowflake guild_id;
  /** the channel ID this webhook is for, if any */
  u64snowflake channel_id;
  /** the user this webhook was created by (not returned when getting a
       webhook with its token) */

  struct discord_user *user;

  /** the default name of the webhook */
  char *name;
  /** the secure token of the webhook (returned for Incoming Webhooks) */
  char *token;
  /** the bot/OAuth2 application that created this webhook */
  u64snowflake application_id;
  /** the guild of the channel that this webhook is following (returned for
       Channel Follower Webhooks) */

  struct discord_channel *source_channel;

  /** the url used for executing the webhook (returned by the webhooks
       OAuth2 flow */
  char *url;
};
struct discord_webhooks {
  int size;
  struct discord_webhook *array;
  int realsize;
};
struct discord_create_webhook {
  /** name of the webhook (1-80 characters) */
  char *name;
  /** image for the default webhook avatar */

  char *avatar;
};
struct discord_modify_webhook {
  /** the default name of the webhook */
  char *name;
  /** image for the default webhook avatar */

  char *avatar;

  /** the new channel ID for this webhook should be moved to */
  u64snowflake channel_id;
};
struct discord_modify_webhook_with_token {
  /** the default name of the webhook */
  char *name;
  /** image for the default webhook avatar */

  char *avatar;
};
struct discord_execute_webhook {
  /** waits for server confirmation of message send before response, and
       returns the created message body (defaults to `false`; when `false` a
       message that is not saved does not return an error) */
  bool wait;
  /** send a message to the specified thread within a webhook's channel; the
       thread will automatically be unarchived */
  u64snowflake thread_id;
  /** the message contents (up to 2000 characters) */
  char *content;
  /** override the default username of the webhook */
  char *username;
  /** override the default avatar of the webhook */
  char *avatar_url;
  /** true if this is a TTS message */
  bool tts;
  /** embedded `rich` content */

  struct discord_embeds *embeds;

  /** allowed mentions for the message */

  struct discord_allowed_mention *allowed_mentions;

  /** the components to include with the message */

  struct discord_components *components;

  /** attachment objects with filename and description */

  struct discord_attachments *attachments;

  /** message flags combined as a bitfield (only `SUPPRESS_EMBEDS` can be
       set) */

  u64snowflake flags;
};
struct discord_get_webhook_message {
  /** ID of the thread the message is in */

  u64snowflake thread_id;
};
struct discord_edit_webhook_message {
  /** id of the thread the message is in */
  u64snowflake thread_id;
  /** the message contents (up to 2000 characters) */
  char *content;
  /** embedded `rich` content */

  struct discord_embeds *embeds;

  /** allowed mentions for the message */

  struct discord_allowed_mention *allowed_mentions;

  /** the components to include with the message */

  struct discord_components *components;

  /** attached files to keep and possible descriptions for new files */

  struct discord_attachments *attachments;
};
struct discord_delete_webhook_message {
  /** ID of the thread the message is in */

  u64snowflake thread_id;
};
#define DISCORD_GATEWAY_GUILDS 1 << 0
#define DISCORD_GATEWAY_GUILD_MEMBERS 1 << 1
#define DISCORD_GATEWAY_GUILD_BANS 1 << 2
#define DISCORD_GATEWAY_GUILD_EMOJIS 1 << 3
#define DISCORD_GATEWAY_GUILD_INTEGRATIONS 1 << 4
#define DISCORD_GATEWAY_GUILD_WEBHOOKS 1 << 5
#define DISCORD_GATEWAY_GUILD_INVITES 1 << 6
#define DISCORD_GATEWAY_GUILD_VOICE_STATES 1 << 7
#define DISCORD_GATEWAY_GUILD_PRESENCES 1 << 8
#define DISCORD_GATEWAY_GUILD_MESSAGES 1 << 9
#define DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS 1 << 10
#define DISCORD_GATEWAY_GUILD_MESSAGE_TYPING 1 << 11
#define DISCORD_GATEWAY_DIRECT_MESSAGES 1 << 12
#define DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS 1 << 13
#define DISCORD_GATEWAY_DIRECT_MESSAGE_TYPING 1 << 14
#define DISCORD_ACTIVITY_INSTANCE 1 << 0
#define DISCORD_ACTIVITY_JOIN 1 << 1
#define DISCORD_ACTIVITY_SPECTATE 1 << 2
#define DISCORD_ACTIVITY_JOIN_REQUEST 1 << 3
#define DISCORD_ACTIVITY_SYNC 1 << 4
#define DISCORD_ACTIVITY_PLAY 1 << 5
#define DISCORD_ACTIVITY_PARTY_PRIVACY_FRIENDS 1 << 6
#define DISCORD_ACTIVITY_PARTY_PRIVACY_VOICE_CHANNEL 1 << 7
#define DISCORD_ACTIVITY_EMBEDDED 1 << 8
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
  DISCORD_GATEWAY_CLOSE_REASON_RECONNECT = 4900
};
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
  DISCORD_GATEWAY_HEARTBEAT_ACK = 11
};
enum discord_gateway_events {
  DISCORD_GATEWAY_EVENTS_NONE = 0,
  DISCORD_GATEWAY_EVENTS_READY = 1,
  DISCORD_GATEWAY_EVENTS_RESUMED = 2,
  DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_CREATE = 3,
  DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_UPDATE = 4,
  DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_DELETE = 5,
  DISCORD_GATEWAY_EVENTS_CHANNEL_CREATE = 6,
  DISCORD_GATEWAY_EVENTS_CHANNEL_UPDATE = 7,
  DISCORD_GATEWAY_EVENTS_CHANNEL_DELETE = 8,
  DISCORD_GATEWAY_EVENTS_CHANNEL_PINS_UPDATE = 9,
  DISCORD_GATEWAY_EVENTS_THREAD_CREATE = 10,
  DISCORD_GATEWAY_EVENTS_THREAD_UPDATE = 11,
  DISCORD_GATEWAY_EVENTS_THREAD_DELETE = 12,
  DISCORD_GATEWAY_EVENTS_THREAD_LIST_SYNC = 13,
  DISCORD_GATEWAY_EVENTS_THREAD_MEMBER_UPDATE = 14,
  DISCORD_GATEWAY_EVENTS_THREAD_MEMBERS_UPDATE = 15,
  DISCORD_GATEWAY_EVENTS_GUILD_CREATE = 16,
  DISCORD_GATEWAY_EVENTS_GUILD_UPDATE = 17,
  DISCORD_GATEWAY_EVENTS_GUILD_DELETE = 18,
  DISCORD_GATEWAY_EVENTS_GUILD_BAN_ADD = 19,
  DISCORD_GATEWAY_EVENTS_GUILD_BAN_REMOVE = 20,
  DISCORD_GATEWAY_EVENTS_GUILD_EMOJIS_UPDATE = 21,
  DISCORD_GATEWAY_EVENTS_GUILD_STICKERS_UPDATE = 22,
  DISCORD_GATEWAY_EVENTS_GUILD_INTEGRATIONS_UPDATE = 23,
  DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_ADD = 24,
  DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_REMOVE = 25,
  DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_UPDATE = 26,
  DISCORD_GATEWAY_EVENTS_GUILD_MEMBERS_CHUNK = 27,
  DISCORD_GATEWAY_EVENTS_GUILD_ROLE_CREATE = 28,
  DISCORD_GATEWAY_EVENTS_GUILD_ROLE_UPDATE = 29,
  DISCORD_GATEWAY_EVENTS_GUILD_ROLE_DELETE = 30,
  DISCORD_GATEWAY_EVENTS_INTEGRATION_CREATE = 31,
  DISCORD_GATEWAY_EVENTS_INTEGRATION_UPDATE = 32,
  DISCORD_GATEWAY_EVENTS_INTEGRATION_DELETE = 33,
  DISCORD_GATEWAY_EVENTS_INTERACTION_CREATE = 34,
  DISCORD_GATEWAY_EVENTS_INVITE_CREATE = 35,
  DISCORD_GATEWAY_EVENTS_INVITE_DELETE = 36,
  DISCORD_GATEWAY_EVENTS_MESSAGE_CREATE = 37,
  DISCORD_GATEWAY_EVENTS_MESSAGE_UPDATE = 38,
  DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE = 39,
  DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE_BULK = 40,
  DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_ADD = 41,
  DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE = 42,
  DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE_ALL = 43,
  DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE_EMOJI = 44,
  DISCORD_GATEWAY_EVENTS_PRESENCE_UPDATE = 45,
  DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_CREATE = 46,
  DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_DELETE = 47,
  DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_UPDATE = 48,
  DISCORD_GATEWAY_EVENTS_TYPING_START = 49,
  DISCORD_GATEWAY_EVENTS_USER_UPDATE = 50,
  DISCORD_GATEWAY_EVENTS_VOICE_STATE_UPDATE = 51,
  DISCORD_GATEWAY_EVENTS_VOICE_SERVER_UPDATE = 52,
  DISCORD_GATEWAY_EVENTS_WEBHOOKS_UPDATE = 53
};
enum discord_activity_types {
  /** Format: \Playing {name}\ */
  DISCORD_ACTIVITY_GAME = 0,
  /** Format: \Streaming {details}\ */
  DISCORD_ACTIVITY_STREAMING = 1,
  /** Format: \Listening to {name}\ */
  DISCORD_ACTIVITY_LISTENING = 2,
  /** Format: \Watching {name}\ */
  DISCORD_ACTIVITY_WATCHING = 3,
  /** Format: \{emoji} {name}\ */
  DISCORD_ACTIVITY_CUSTOM = 4,
  /** Format: \Competing in {name}\ */
  DISCORD_ACTIVITY_COMPETING = 5
};
struct discord_identify {
  /** authentication token */
  char *token;
  /** connection properties */
  struct discord_identify_connection *properties;
  /** whether this connection supports compression packets */
  bool compress;
  /** value between 50 and 250, total number of members where the gateway
       will stop sending offline members in the guild member list */
  int large_threshold;
  /** presence structure for initial presence information */
  struct discord_presence_update *presence;
  /** the gateway intents you wish to receive */
  int intents;
};
struct discord_identify_connection {
  /** your operating system */
  char *os;
  /** your library name */
  char *browser;
  /** your library name */
  char *device;
};
struct discord_voice_state_status {
  /** ID of the guild */
  u64snowflake guild_id;
  /** ID of the voice channel client wants to join (null if disconnecting) */
  u64snowflake channel_id;
  /** is the client muted */
  bool self_mute;
  /** is the client deafened */
  bool self_deaf;
};
struct discord_presence_update {
  /** unix time (in milliseconds) of when the client went idle, or null if
       the client is not idle */
  u64unix_ms since;
  /** the user's activities */
  struct discord_activities *activities;
  /** the user's new status */
  char *status;
  /** whether or not the client is afk */
  bool afk;
};
struct discord_presence_updates {
  int size;
  struct discord_presence_update *array;
  int realsize;
};
struct discord_activity {
  /** the activity's name */
  char *name;
  /** activity type */
  enum discord_activity_types type;
  /** stream url, is validated when type is 1 */
  char *url;
  /** unix timestamp (in milliseconds)of when the activity was added to the
       user's session */
  u64unix_ms created_at;
  /** unix timestamps for start and/or end of the game */
  struct discord_activity_timestamps *timestamps;
  /** application ID for the game */
  u64snowflake application_id;
  /** what the player is currently doing */
  char *details;
  /** the user's current party status */
  char *state;
  /** the emoji used for a custom status */
  struct discord_activity_emoji *emoji;
  /** information for the current party of the player */
  struct discord_activity_party *party;
  /** images for the presence and their hover texts */
  struct discord_activity_assets *assets;
  /** secrets for Rich Presence joining and spectating */
  struct discord_activity_secrets *secrets;
  /** whether or not the activity is an instanced game session */
  bool instance;
  /** activity flags bitwise mask, describes what they payload includes */
  u64snowflake flags;
  /** the custom buttons shown in the Rich Presence (max 2) */
  struct discord_activity_buttons *buttons;
};
struct discord_activities {
  int size;
  struct discord_activity *array;
  int realsize;
};
struct discord_activity_timestamps {
  /** unix timestamp (in milliseconds)of when the activity started */
  u64unix_ms start;
  /** unix timestamp (in milliseconds)of when the activity ends */
  u64unix_ms end;
};
struct discord_activity_emoji {
  /** the name of the emoji */
  char *name;
  /** the ID of the emoji */

  u64snowflake id;

  /** whether this emoji is animated */
  bool animated;
};
struct discord_activity_party {
  /** the ID of the party */
  char *id;
  /** used to show the party's current and maximum size @note array of two
       integers (current_size, max_size) */
  struct integers *size;
};
struct discord_activity_assets {
  /** activity large asset image */
  char *large_image;
  /** text displayed when hovering over the large image of the activity */
  char *large_text;
  /** activity small asset image */
  char *small_image;
  /** text displayed when hovering over the small image of the activity */
  char *small_text;
};
struct discord_activity_secrets {
  /** the secret for joining a party */
  char *join;
  /** the secret for spectating a game */
  char *spectate;
  /** the secret for a specific instanced match */
  char *match;
};
struct discord_activity_button {
  /** the text shown on the button (1-32 characters) */
  char *label;
  /** the url opened when clicking the button (1-512 characters) */
  char *url;
};
struct discord_activity_buttons {
  int size;
  struct discord_activity_button *array;
  int realsize;
};
struct discord_session_start_limit {
  /** the total number of session starts the current user is allowed */
  int total;
  /** the remaining number of session starts the current user is allowed */
  int remaining;
  /** the number of milliseconds after which the limit resets */
  int reset_after;
  /** the number of identify requests allowed per 5 seconds */
  int max_concurrency;
};
enum discord_membership_state {
  DISCORD_MEMBERSHIP_INVITED = 1,
  DISCORD_MEMBERSHIP_ACCEPTED = 2
};
struct discord_team {
  /** a hash image of the team's icon */
  char *icon;
  /** the unique ID of the team */
  u64snowflake id;
  /** the members of the team */

  struct discord_team_members *members;

  /** the name of the team */
  char *name;
  /** the user ID of the current team owner */
  u64snowflake owner_user_id;
};
struct discord_team_member {
  /** the user's membership state on the team */
  enum discord_membership_state membership_state;
  /** will always be \[\*\]\ */

  struct strings *permissions;

  /** the ID of the parent team of which they are a member */
  u64snowflake team_id;
  /** the avatar, discriminator, id,and username of the user */

  struct discord_user *user;
};
struct discord_team_members {
  int size;
  struct discord_team_member *array;
  int realsize;
};
enum discord_voice_close_opcodes {
  /** You sent an invalid opcode */
  DISCORD_VOICE_CLOSE_REASON_UNKNOWN_OPCODE = 4001,
  /** You sent a invalid payload in your identifying to the Gateway */
  DISCORD_VOICE_CLOSE_REASON_DECODE_ERROR = 4002,
  /** You sent a payload before identifying with the gateway */
  DISCORD_VOICE_CLOSE_REASON_NOT_AUTHENTICATED = 4003,
  /** The token you sent in your identify payload is incorrect */
  DISCORD_VOICE_CLOSE_REASON_AUTHENTICATION_FAILED = 4004,
  /** You sent more than one identify payload */
  DISCORD_VOICE_CLOSE_REASON_ALREADY_AUTHENTICATED = 4005,
  /** Your session is no longer validd */
  DISCORD_VOICE_CLOSE_REASON_INVALID_SESSION = 4006,
  /** Your session has timed out */
  DISCORD_VOICE_CLOSE_REASON_SESSION_TIMED_OUT = 4009,
  /** Discord can't find the server you're trying to connect to */
  DISCORD_VOICE_CLOSE_REASON_SERVER_NOT_FOUND = 4011,
  /** Discord didn't recognize the protocol you sent */
  DISCORD_VOICE_CLOSE_REASON_UNKNOWN_PROTOCOL = 4012,
  /** Channel was deleted, you were kicked, voice server changed, or the main
       gateway session was dropped; should not reconnect */
  DISCORD_VOICE_CLOSE_REASON_DISCONNECTED = 4014,
  /** The server crashed, try resuming */
  DISCORD_VOICE_CLOSE_REASON_SERVER_CRASH = 4015,
  /** Discord didn't recognize the encryption */
  DISCORD_VOICE_CLOSE_REASON_UNKNOWN_ENCRYPTION_MODE = 4016
};
enum discord_voice_opcodes {
  /** Begin a voice websocket connection */
  DISCORD_VOICE_IDENTIFY = 0,
  /** Select the voice protocol */
  DISCORD_VOICE_SELECT_PROTOCOL = 1,
  /** Complete the websocket handshake */
  DISCORD_VOICE_READY = 2,
  /** Keep the websocket connection alive */
  DISCORD_VOICE_HEARTBEAT = 3,
  /** Describe the session */
  DISCORD_VOICE_SESSION_DESCRIPTION = 4,
  /** Indicate which users are speaking */
  DISCORD_VOICE_SPEAKING = 5,
  /** Sent to acknowledge a received client heartbeat */
  DISCORD_VOICE_HEARTBEAT_ACK = 6,
  /** Resume a connection */
  DISCORD_VOICE_RESUME = 7,
  /** Time to wait between sending heartbeats in milliseconds */
  DISCORD_VOICE_HELLO = 8,
  /** Acknowledge a successful session resume */
  DISCORD_VOICE_RESUMED = 9,
  /** A client has disconnected from the voice channel */
  DISCORD_VOICE_CLIENT_DISCONNECT = 13,
  DISCORD_VOICE_CODEC = 14
};
enum discord_voice_speaking_flags {
  /** Normal transmission of voice audio */
  DISCORD_VOICE_MICROPHONE = 1 << 0,
  /** Transmission of context audio for video, no speaking indicators */
  DISCORD_VOICE_SOUNDSHARE = 1 << 1,
  /** Priority speaker, lowering audio of other speakers */
  DISCORD_VOICE_PRIORITY = 1 << 2
};
enum discord_application_command_types {
  /** Slash commands: a text-based command that shows up when a user
       types `/` */
  DISCORD_APPLICATION_CHAT_INPUT = 1,
  /** A UI-based command that shows up when a user
       right clicks or taps on another user */
  DISCORD_APPLICATION_USER = 2,
  /** A UI-based command that shows up when a user
       right clicks or tap on a message */
  DISCORD_APPLICATION_MESSAGE = 3
};
enum discord_application_command_option_types {
  DISCORD_APPLICATION_OPTION_SUB_COMMAND = 1,
  DISCORD_APPLICATION_OPTION_SUB_COMMAND_GROUP = 2,
  DISCORD_APPLICATION_OPTION_STRING = 3,
  /** Any integer between `-2^53` and `2^53` */
  DISCORD_APPLICATION_OPTION_INTEGER = 4,
  DISCORD_APPLICATION_OPTION_BOOLEAN = 5,
  DISCORD_APPLICATION_OPTION_USER = 6,
  /** Includes all channel types + categories */
  DISCORD_APPLICATION_OPTION_CHANNEL = 7,
  DISCORD_APPLICATION_OPTION_ROLE = 8,
  /** Includes users and roles */
  DISCORD_APPLICATION_OPTION_MENTIONABLE = 9,
  /** Any double between `-2^53` and `2^53` */
  DISCORD_APPLICATION_OPTION_NUMBER = 10,
  /** @ref discord_attachment object */
  DISCORD_APPLICATION_OPTION_ATTACHMENT = 11
};
enum discord_application_command_permission_types {
  DISCORD_APPLICATION_PERMISSION_ROLE = 1,
  DISCORD_APPLICATION_PERMISSION_USER = 2
};
struct discord_application_command {
  /** unique ID of the command */
  u64snowflake id;
  /** one of application command types */

  enum discord_application_command_types type;

  /** unique ID of the parent application */
  u64snowflake application_id;

  /** guild ID of the command, if not global */
  u64snowflake guild_id;

  /** 1-32 character name */
  char *name;
  /** 1-100 character description for `CHAT_INPUT` commands, empty string
       for `USER` and `MESSAGE` commands */
  char *description;
  /** the parameters for the command, max 25 */

  struct discord_application_command_options *options;

  /** whether the command is enabled by default when the app is added to a
       guild */

  bool default_permission;

  /** autoincrementing version identifier updated during substantial
       record changes */
  u64snowflake version;
};
struct discord_application_commands {
  int size;
  struct discord_application_command *array;
  int realsize;
};
struct discord_application_command_option {
  /** value of application command option type */
  enum discord_application_command_option_types type;
  /** 1-32 character name */
  char *name;
  /** 1-100 character description */
  char *description;
  /** if the parameter is required or optional -- default `false` */

  bool required;

  /** choices for string and int types for the user to pick from */

  struct discord_application_command_option_choices *choices;

  /** if the option is a subcommand or subcommand group type, this nested
       options will be the parameters */

  struct discord_application_command_options *options;

  /** if the option is a channel type, the channels shown will be restricted
       to these types */

  struct integers *channel_types;

  /** if the option is an INTEGER or NUMBER type, the minimum value permitted */

  char *min_value;

  /** if the option is an INTEGER or NUMBER type, the maximum value permitted */

  char *max_value;

  /** enable autocomplete interactions for this option */

  bool autocomplete;
};
struct discord_application_command_options {
  int size;
  struct discord_application_command_option *array;
  int realsize;
};
struct discord_application_command_option_choice {
  /** 1-100 character choice name */
  char *name;
  /** value of the choice, up to 100 characters if string @note in case of a
       string the value must be enclosed with escaped commas, ex: `\hi\` */
  json_char *value;
};
struct discord_application_command_option_choices {
  int size;
  struct discord_application_command_option_choice *array;
  int realsize;
};
struct discord_application_command_interaction_data_option {
  /** the name of the parameter */
  char *name;
  /** value of the application command option type */
  enum discord_application_command_option_types type;
  /** the value of the option resulting from user input @note in case of a
       string the value must be enclosed with escaped commands, ex: `\hi\` */

  json_char *value;

  /** present if this option is a group or subcommand */

  struct discord_application_command_interaction_data_options *options;

  /** true if this option is the currently focused option for autocomplete */
  bool focused;
};
struct discord_application_command_interaction_data_options {
  int size;
  struct discord_application_command_interaction_data_option *array;
  int realsize;
};
struct discord_guild_application_command_permission {
  /** the ID of the command */
  u64snowflake id;
  /** the ID of the application the command belongs to */
  u64snowflake application_id;
  /** the ID of the guild */
  u64snowflake guild_id;
  /** the permissions for the command in the guild */
  struct discord_application_command_permissions *permissions;
};
struct discord_guild_application_command_permissions {
  int size;
  struct discord_guild_application_command_permission *array;
  int realsize;
};
struct discord_application_command_permission {
  /** the ID of the role or user */
  u64snowflake id;
  /** role or user */
  enum discord_application_command_permission_types type;
  /** `true` to allow, `false` to disallow */
  bool permission;
};
struct discord_application_command_permissions {
  int size;
  struct discord_application_command_permission *array;
  int realsize;
};
struct discord_create_global_application_command {
  /** 1-32 lowercase character name */
  char *name;
  /** 1-100 character description */
  char *description;
  /** the parameters for the command */

  struct discord_application_command_options *options;

  /** whether the command is enabled by default when the app is added to a
       guild */
  bool default_permission;
  /** the type of command, default `1` if not set */

  enum discord_application_command_types type;
};
struct discord_edit_global_application_command {
  /** 1-32 lowercase character name */
  char *name;
  /** 1-100 character description */
  char *description;
  /** the parameters for the command */

  struct discord_application_command_options *options;

  /** whether the command is enabled by default when the app is added to a
       guild */
  bool default_permission;
};
struct discord_create_guild_application_command {
  /** 1-32 lowercase character name */
  char *name;
  /** 1-100 character description */
  char *description;
  /** the parameters for the command */

  struct discord_application_command_options *options;

  /** whether the command is enabled by default when the app is added to a
       guild */
  bool default_permission;
  /** the type of command, default `1` if not set */

  enum discord_application_command_types type;
};
struct discord_edit_guild_application_command {
  /** 1-32 lowercase character name */
  char *name;
  /** 1-100 character description */
  char *description;
  /** the parameters for the command */

  struct discord_application_command_options *options;

  /** whether the command is enabled by default when the app is added to a
       guild */
  bool default_permission;
};
struct discord_edit_application_command_permissions {
  /** the permissions for the command in the guild */

  struct discord_application_command_permissions *permissions;
};
enum discord_component_types {
  /** a container for the other components */
  DISCORD_COMPONENT_ACTION_ROW = 1,
  /** a button object */
  DISCORD_COMPONENT_BUTTON = 2,
  /** a select menu for picking from choices */
  DISCORD_COMPONENT_SELECT_MENU = 3,
  /** a text input object */
  DISCORD_COMPONENT_TEXT_INPUT = 4
};
enum discord_component_styles {
  /** blurple */
  DISCORD_BUTTON_PRIMARY = 1,
  /** grey */
  DISCORD_BUTTON_SECONDARY = 2,
  /** green */
  DISCORD_BUTTON_SUCCESS = 3,
  /** red */
  DISCORD_BUTTON_DANGER = 4,
  /** grey, navigates to a URL */
  DISCORD_BUTTON_LINK = 5,
  /** a single-line input */
  DISCORD_TEXT_SHORT = 1,
  /** a multi-line input */
  DISCORD_TEXT_PARAGRAPH = 2
};
struct discord_component {
  /** component type */

  enum discord_component_types type;

  /** a developer-defined identifier for the component, max 100 characters */
  char *custom_id;
  /** whether the component is disabled, default `false` */
  bool disabled;
  /** one of button or text styles */

  enum discord_component_styles style;

  /** text that appears on the button, max 80 characters */
  char *label;
  /** `name`, `id`, and `animated` */

  struct discord_emoji *emoji;

  /** a url for link-style buttons */
  char *url;
  /** the choices in the select, max 25 */

  struct discord_select_options *options;

  /** custom placeholder text if nothing is selected, max 100 characters */
  char *placeholder;
  /** the minimum number of items that must be chosen: default 1, min 0,
       max 25 */

  int min_values;

  /** the maximum number of items that must be chosen: default 1, max 25 */

  int max_values;

  /** a list of child components */

  struct discord_components *components;

  /** the minimum input length for a text input */
  int min_length;
  /** the maximum input length for a text input */
  int max_length;
  /** whether this componentis required to be filled */
  bool required;
  /** a pre-filled value for this component */
  char *value;
};
struct discord_components {
  int size;
  struct discord_component *array;
  int realsize;
};
struct discord_select_option {
  /** the user-facing name of the option, max 100 characters */
  char *label;
  /** the dev-define value of the option, max 100 characters */
  char *value;
  /** an additional description of the option, max 100 characters */
  char *description;
  /** `id`, `name`, and `animated` */

  struct discord_emoji *emoji;

  /** will render this option as selected by default */
  bool Default;
};
struct discord_select_options {
  int size;
  struct discord_select_option *array;
  int realsize;
};
enum discord_interaction_types {
  DISCORD_INTERACTION_PING = 1,
  DISCORD_INTERACTION_APPLICATION_COMMAND = 2,
  DISCORD_INTERACTION_MESSAGE_COMPONENT = 3,
  DISCORD_INTERACTION_APPLICATION_COMMAND_AUTOCOMPLETE = 4,
  DISCORD_INTERACTION_MODAL_SUBMIT = 5
};
enum discord_interaction_callback_types {
  /** ACK a @ref DISCORD_INTERACTION_PING */
  DISCORD_INTERACTION_PONG = 1,
  /** respond to an interaction with a message */
  DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE = 4,
  /** ACK an interaction and edit a response later, the user sees a loading
       state */
  DISCORD_INTERACTION_DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE = 5,
  /** for components, ACK an interaction and edit the original message later
       the user does not see a loading state */
  DISCORD_INTERACTION_DEFERRED_UPDATE_MESSAGE = 6,
  /** for components, edit the message the component was attached to */
  DISCORD_INTERACTION_UPDATE_MESSAGE = 7,
  /** respond to an autocomplete interaction with suggested choices */
  DISCORD_INTERACTION_APPLICATION_COMMAND_AUTOCOMPLETE_RESULT = 8,
  /** respond to an interaction with a popup modal */
  DISCORD_INTERACTION_MODAL = 9
};
struct discord_interaction {
  /** ID of the interaction */
  u64snowflake id;
  /** ID of the application this interaction is for */
  u64snowflake application_id;
  /** the type of the interaction */
  enum discord_interaction_types type;
  /** the command data payload */
  struct discord_interaction_data *data;
  /** the guild it was sent from */
  u64snowflake guild_id;
  /** the channel it was sent from */
  u64snowflake channel_id;
  /** guild member data for the invoking user, including permissions */
  struct discord_guild_member *member;
  /** user object for the invoking user, if invoked in a DM */
  struct discord_user *user;
  /** a continuation token for responding to the interaction */
  char *token;
  /** read-only property, always `1` */
  int version;
  /** for components, the message they were attached to */
  struct discord_message *message;
  /** the selected language of the invoking user */
  char *locale;
  /** the guild preferred locale, if invoked in a guild */
  char *guild_locale;
};
struct discord_interaction_data {
  /** the ID of the invoked command */
  u64snowflake id;
  /** the name of the invoked command */
  char *name;
  /** the type of the invoked command */
  enum discord_application_command_types type;
  /** converted users + roles + channels + attachments */
  struct discord_resolved_data *resolved;
  /** the params + values from the user */
  struct discord_application_command_interaction_data_options *options;
  /** the custom_id of the component */
  char *custom_id;
  /** the type of the component */
  enum discord_component_types component_type;
  /** the values the user selected */
  struct strings *values;
  /** the ID of the user or messaged targetted by a user or message command */
  u64snowflake target_id;
  /** the values submitted by the user */
  struct discord_components *components;
};
struct discord_resolved_data {
  /** the IDs and @ref discord_user datatypes */
  struct snowflakes *users;
  /** the IDs and partial @ref discord_guild_member datatypes */
  struct snowflakes *members;
  /** the IDs and @ref discord_role datatypes */
  struct snowflakes *roles;
  /** the IDs and partial @ref discord_channel datatypes */
  struct snowflakes *channels;
  /** the IDs and partial @ref discord_message datatypes */
  struct snowflakes *messages;
  /** the IDs and partial @ref discord_attachment datatypes */
  struct snowflakes *attachments;
};
struct discord_message_interaction {
  /** ID of the interaction */
  u64snowflake id;
  /** the type of interaction */
  enum discord_interaction_types type;
  /** the name of the application command */
  char *name;
  /** the user who invoked the interaction */
  struct discord_user *user;
  /** the member who invoked the interaction in the guild */
  struct discord_guild_member *member;
};
struct discord_interaction_response {
  /** interaction callback type */
  enum discord_interaction_callback_types type;
  /** an optional response message */

  struct discord_interaction_callback_data *data;
};
struct discord_interaction_callback_data {
  /** message components */

  struct discord_components *components;

  /** is the response TTS */

  bool tts;

  /** message content */

  char *content;

  /** supports up to 10 embeds */

  struct discord_embeds *embeds;

  /** message flags combined as a bitfield (only
       @ref DISCORD_MESSAGE_SUPRESS_EMBEDS and @ref DISCORD_MESSAGE_EPHEMERAL
       can be set) */

  enum discord_message_flags flags;

  /** attachment objects with filename and description */

  struct discord_attachments *attachments;

  /** autocomplete choices (max of 25 choices) */
  struct discord_application_command_option_choices *choices;
  /** a developer defined identifier for the component, max 100 characters */
  char *custom_id;
  /** the title of the popup modal */
  char *title;
};
struct discord_edit_original_interaction_response {
  /** id of the thread the message is in */
  u64snowflake thread_id;
  /** the message contents (up to 2000 characters) */
  char *content;
  /** embedded `rich` content */

  struct discord_embeds *embeds;

  /** allowed mentions for the message */

  struct discord_allowed_mention *allowed_mentions;

  /** the components to include with the message */

  struct discord_components *components;

  /** attached files to keep and possible descriptions for new files */

  struct discord_attachments *attachments;
};
struct discord_create_followup_message {
  /** waits for server confirmation of message send before response, and
       returns the created message body (defaults to `false`; when `false` a
       message that is not saved does not return an error) */
  bool wait;
  /** send a message to the specified thread within a webhook's channel; the
       thread will automatically be unarchived */
  u64snowflake thread_id;
  /** override the default avatar of the webhook */
  char *avatar_url;
  /** true if this is a TTS message */
  bool tts;
  /** embedded `rich` content */

  struct discord_embeds *embeds;

  /** allowed mentions for the message */

  struct discord_allowed_mention *allowed_mentions;

  /** the components to include with the message */

  struct discord_components *components;

  /** attachment objects with filename and description */

  struct discord_attachments *attachments;

  /** message flags combined as a bitfield (only `SUPPRESS_EMBEDS` can be
       set) */

  u64snowflake flags;
};
struct discord_edit_followup_message {
  /** id of the thread the message is in */
  u64snowflake thread_id;
  /** the message contents (up to 2000 characters) */
  char *content;
  /** embedded `rich` content */

  struct discord_embeds *embeds;

  /** allowed mentions for the message */

  struct discord_allowed_mention *allowed_mentions;

  /** the components to include with the message */

  struct discord_components *components;

  /** attached files to keep and possible descriptions for new files */

  struct discord_attachments *attachments;
};
void strings_cleanup(struct strings *this);

void json_values_cleanup(struct json_values *this);

void snowflakes_cleanup(struct snowflakes *this);

void integers_cleanup(struct integers *this);

void discord_role_init(struct discord_role *this);
void discord_role_cleanup(struct discord_role *this);

void discord_roles_cleanup(struct discord_roles *this);

void discord_application_init(struct discord_application *this);
void discord_application_cleanup(struct discord_application *this);

void discord_audit_log_init(struct discord_audit_log *this);
void discord_audit_log_cleanup(struct discord_audit_log *this);

void discord_invite_init(struct discord_invite *this);
void discord_invite_cleanup(struct discord_invite *this);

void discord_invites_cleanup(struct discord_invites *this);

void discord_get_invite_init(struct discord_get_invite *this);
void discord_get_invite_cleanup(struct discord_get_invite *this);

void discord_channel_init(struct discord_channel *this);
void discord_channel_cleanup(struct discord_channel *this);

void discord_channels_cleanup(struct discord_channels *this);

void discord_message_init(struct discord_message *this);
void discord_message_cleanup(struct discord_message *this);

void discord_messages_cleanup(struct discord_messages *this);

void discord_followed_channel_init(struct discord_followed_channel *this);
void discord_followed_channel_cleanup(struct discord_followed_channel *this);

void discord_thread_members_cleanup(struct discord_thread_members *this);

void discord_attachments_cleanup(struct discord_attachments *this);

void discord_embed_init(struct discord_embed *this);
void discord_embed_cleanup(struct discord_embed *this);

void discord_embeds_cleanup(struct discord_embeds *this);

void discord_embed_thumbnail_init(struct discord_embed_thumbnail *this);
void discord_embed_thumbnail_cleanup(struct discord_embed_thumbnail *this);

void discord_embed_video_init(struct discord_embed_video *this);
void discord_embed_video_cleanup(struct discord_embed_video *this);

void discord_embed_image_init(struct discord_embed_image *this);
void discord_embed_image_cleanup(struct discord_embed_image *this);

void discord_embed_provider_init(struct discord_embed_provider *this);
void discord_embed_provider_cleanup(struct discord_embed_provider *this);

void discord_embed_author_init(struct discord_embed_author *this);
void discord_embed_author_cleanup(struct discord_embed_author *this);

void discord_embed_footer_init(struct discord_embed_footer *this);
void discord_embed_footer_cleanup(struct discord_embed_footer *this);

void discord_embed_field_init(struct discord_embed_field *this);
void discord_embed_field_cleanup(struct discord_embed_field *this);

void discord_embed_fields_cleanup(struct discord_embed_fields *this);

void
discord_thread_response_body_init(struct discord_thread_response_body *this);
void
discord_thread_response_body_cleanup(struct discord_thread_response_body *this);

void discord_modify_channel_init(struct discord_modify_channel *this);
void discord_modify_channel_cleanup(struct discord_modify_channel *this);

void
discord_get_channel_messages_init(struct discord_get_channel_messages *this);
void
discord_get_channel_messages_cleanup(struct discord_get_channel_messages *this);

void discord_create_message_init(struct discord_create_message *this);
void discord_create_message_cleanup(struct discord_create_message *this);

void discord_get_reactions_init(struct discord_get_reactions *this);
void discord_get_reactions_cleanup(struct discord_get_reactions *this);

void discord_edit_message_init(struct discord_edit_message *this);
void discord_edit_message_cleanup(struct discord_edit_message *this);

void
discord_bulk_delete_messages_init(struct discord_bulk_delete_messages *this);
void
discord_bulk_delete_messages_cleanup(struct discord_bulk_delete_messages *this);

void discord_edit_channel_permissions_init(
    struct discord_edit_channel_permissions *this);
void discord_edit_channel_permissions_cleanup(
    struct discord_edit_channel_permissions *this);

void
discord_create_channel_invite_init(struct discord_create_channel_invite *this);
void discord_create_channel_invite_cleanup(
    struct discord_create_channel_invite *this);

void discord_follow_news_channel_init(struct discord_follow_news_channel *this);
void
discord_follow_news_channel_cleanup(struct discord_follow_news_channel *this);

void discord_group_dm_add_recipient_init(
    struct discord_group_dm_add_recipient *this);
void discord_group_dm_add_recipient_cleanup(
    struct discord_group_dm_add_recipient *this);

void discord_start_thread_with_message_init(
    struct discord_start_thread_with_message *this);
void discord_start_thread_with_message_cleanup(
    struct discord_start_thread_with_message *this);

void discord_start_thread_without_message_init(
    struct discord_start_thread_without_message *this);
void discord_start_thread_without_message_cleanup(
    struct discord_start_thread_without_message *this);

void discord_list_active_threads_init(struct discord_list_active_threads *this);
void
discord_list_active_threads_cleanup(struct discord_list_active_threads *this);

void discord_emoji_init(struct discord_emoji *this);
void discord_emoji_cleanup(struct discord_emoji *this);

void discord_emojis_cleanup(struct discord_emojis *this);

void discord_create_guild_emoji_init(struct discord_create_guild_emoji *this);
void
discord_create_guild_emoji_cleanup(struct discord_create_guild_emoji *this);

void discord_modify_guild_emoji_init(struct discord_modify_guild_emoji *this);
void
discord_modify_guild_emoji_cleanup(struct discord_modify_guild_emoji *this);

void discord_guild_init(struct discord_guild *this);
void discord_guild_cleanup(struct discord_guild *this);

void discord_guilds_cleanup(struct discord_guilds *this);

void discord_guild_preview_init(struct discord_guild_preview *this);
void discord_guild_preview_cleanup(struct discord_guild_preview *this);

void discord_guild_member_init(struct discord_guild_member *this);
void discord_guild_member_cleanup(struct discord_guild_member *this);

void discord_guild_members_cleanup(struct discord_guild_members *this);

void discord_ban_init(struct discord_ban *this);
void discord_ban_cleanup(struct discord_ban *this);

void discord_bans_cleanup(struct discord_bans *this);

void discord_welcome_screen_init(struct discord_welcome_screen *this);
void discord_welcome_screen_cleanup(struct discord_welcome_screen *this);

void discord_create_guild_init(struct discord_create_guild *this);
void discord_create_guild_cleanup(struct discord_create_guild *this);

void discord_modify_guild_init(struct discord_modify_guild *this);
void discord_modify_guild_cleanup(struct discord_modify_guild *this);

void
discord_create_guild_channel_init(struct discord_create_guild_channel *this);
void
discord_create_guild_channel_cleanup(struct discord_create_guild_channel *this);

void discord_modify_guild_channel_positions_cleanup(
    struct discord_modify_guild_channel_positions *this);

void discord_list_active_guild_threads_init(
    struct discord_list_active_guild_threads *this);
void discord_list_active_guild_threads_cleanup(
    struct discord_list_active_guild_threads *this);

void discord_add_guild_member_init(struct discord_add_guild_member *this);
void discord_add_guild_member_cleanup(struct discord_add_guild_member *this);

void discord_modify_guild_member_init(struct discord_modify_guild_member *this);
void
discord_modify_guild_member_cleanup(struct discord_modify_guild_member *this);

void
discord_modify_current_member_init(struct discord_modify_current_member *this);
void discord_modify_current_member_cleanup(
    struct discord_modify_current_member *this);

void discord_modify_current_user_nick_init(
    struct discord_modify_current_user_nick *this);
void discord_modify_current_user_nick_cleanup(
    struct discord_modify_current_user_nick *this);

void discord_create_guild_ban_init(struct discord_create_guild_ban *this);
void discord_create_guild_ban_cleanup(struct discord_create_guild_ban *this);

void discord_create_guild_role_init(struct discord_create_guild_role *this);
void discord_create_guild_role_cleanup(struct discord_create_guild_role *this);

void discord_modify_guild_role_positions_cleanup(
    struct discord_modify_guild_role_positions *this);

void discord_modify_guild_role_init(struct discord_modify_guild_role *this);
void discord_modify_guild_role_cleanup(struct discord_modify_guild_role *this);

void discord_begin_guild_prune_init(struct discord_begin_guild_prune *this);
void discord_begin_guild_prune_cleanup(struct discord_begin_guild_prune *this);

void discord_modify_guild_welcome_screen_init(
    struct discord_modify_guild_welcome_screen *this);
void discord_modify_guild_welcome_screen_cleanup(
    struct discord_modify_guild_welcome_screen *this);

void discord_modify_current_user_voice_state_init(
    struct discord_modify_current_user_voice_state *this);
void discord_modify_current_user_voice_state_cleanup(
    struct discord_modify_current_user_voice_state *this);

void discord_modify_user_voice_state_init(
    struct discord_modify_user_voice_state *this);
void discord_modify_user_voice_state_cleanup(
    struct discord_modify_user_voice_state *this);

void
discord_guild_scheduled_event_init(struct discord_guild_scheduled_event *this);
void discord_guild_scheduled_event_cleanup(
    struct discord_guild_scheduled_event *this);

void discord_guild_scheduled_events_cleanup(
    struct discord_guild_scheduled_events *this);

void discord_list_scheduled_events_for_guild_init(
    struct discord_list_scheduled_events_for_guild *this);
void discord_list_scheduled_events_for_guild_cleanup(
    struct discord_list_scheduled_events_for_guild *this);

void discord_create_guild_scheduled_event_init(
    struct discord_create_guild_scheduled_event *this);
void discord_create_guild_scheduled_event_cleanup(
    struct discord_create_guild_scheduled_event *this);

void discord_get_guild_scheduled_event_init(
    struct discord_get_guild_scheduled_event *this);
void discord_get_guild_scheduled_event_cleanup(
    struct discord_get_guild_scheduled_event *this);

void discord_modify_guild_scheduled_event_init(
    struct discord_modify_guild_scheduled_event *this);
void discord_modify_guild_scheduled_event_cleanup(
    struct discord_modify_guild_scheduled_event *this);

void discord_get_guild_scheduled_event_users_init(
    struct discord_get_guild_scheduled_event_users *this);
void discord_get_guild_scheduled_event_users_cleanup(
    struct discord_get_guild_scheduled_event_users *this);

void discord_guild_template_init(struct discord_guild_template *this);
void discord_guild_template_cleanup(struct discord_guild_template *this);

void discord_create_guild_from_guild_template_init(
    struct discord_create_guild_from_guild_template *this);
void discord_create_guild_from_guild_template_cleanup(
    struct discord_create_guild_from_guild_template *this);

void
discord_create_guild_template_init(struct discord_create_guild_template *this);
void discord_create_guild_template_cleanup(
    struct discord_create_guild_template *this);

void
discord_modify_guild_template_init(struct discord_modify_guild_template *this);
void discord_modify_guild_template_cleanup(
    struct discord_modify_guild_template *this);

void discord_stage_instance_init(struct discord_stage_instance *this);
void discord_stage_instance_cleanup(struct discord_stage_instance *this);

void
discord_create_stage_instance_init(struct discord_create_stage_instance *this);
void discord_create_stage_instance_cleanup(
    struct discord_create_stage_instance *this);

void
discord_modify_stage_instance_init(struct discord_modify_stage_instance *this);
void discord_modify_stage_instance_cleanup(
    struct discord_modify_stage_instance *this);

void discord_sticker_init(struct discord_sticker *this);
void discord_sticker_cleanup(struct discord_sticker *this);

void
discord_modify_guild_sticker_init(struct discord_modify_guild_sticker *this);
void
discord_modify_guild_sticker_cleanup(struct discord_modify_guild_sticker *this);

void discord_user_init(struct discord_user *this);
void discord_user_cleanup(struct discord_user *this);

void discord_users_cleanup(struct discord_users *this);

void discord_connections_cleanup(struct discord_connections *this);

void discord_modify_current_user_init(struct discord_modify_current_user *this);
void
discord_modify_current_user_cleanup(struct discord_modify_current_user *this);

void discord_create_dm_init(struct discord_create_dm *this);
void discord_create_dm_cleanup(struct discord_create_dm *this);

void discord_create_group_dm_init(struct discord_create_group_dm *this);
void discord_create_group_dm_cleanup(struct discord_create_group_dm *this);

void discord_voice_state_init(struct discord_voice_state *this);
void discord_voice_state_cleanup(struct discord_voice_state *this);

void discord_voice_states_cleanup(struct discord_voice_states *this);

void discord_voice_regions_cleanup(struct discord_voice_regions *this);

void discord_webhook_init(struct discord_webhook *this);
void discord_webhook_cleanup(struct discord_webhook *this);

void discord_webhooks_cleanup(struct discord_webhooks *this);

void discord_create_webhook_init(struct discord_create_webhook *this);
void discord_create_webhook_cleanup(struct discord_create_webhook *this);

void discord_modify_webhook_init(struct discord_modify_webhook *this);
void discord_modify_webhook_cleanup(struct discord_modify_webhook *this);

void discord_modify_webhook_with_token_init(
    struct discord_modify_webhook_with_token *this);
void discord_modify_webhook_with_token_cleanup(
    struct discord_modify_webhook_with_token *this);

void discord_execute_webhook_init(struct discord_execute_webhook *this);
void discord_execute_webhook_cleanup(struct discord_execute_webhook *this);

void
discord_edit_webhook_message_init(struct discord_edit_webhook_message *this);
void
discord_edit_webhook_message_cleanup(struct discord_edit_webhook_message *this);

void discord_identify_init(struct discord_identify *this);
void discord_identify_cleanup(struct discord_identify *this);

void discord_voice_state_status_init(struct discord_voice_state_status *this);
void
discord_voice_state_status_cleanup(struct discord_voice_state_status *this);

void discord_presence_update_init(struct discord_presence_update *this);
void discord_presence_update_cleanup(struct discord_presence_update *this);

void discord_session_start_limit_init(struct discord_session_start_limit *this);
void
discord_session_start_limit_cleanup(struct discord_session_start_limit *this);

void discord_team_init(struct discord_team *this);
void discord_team_cleanup(struct discord_team *this);

void discord_application_command_init(struct discord_application_command *this);
void
discord_application_command_cleanup(struct discord_application_command *this);

void
discord_application_commands_cleanup(struct discord_application_commands *this);

void discord_guild_application_command_permissions_cleanup(
    struct discord_guild_application_command_permissions *this);

void discord_application_command_permission_init(
    struct discord_application_command_permission *this);
void discord_application_command_permission_cleanup(
    struct discord_application_command_permission *this);

void discord_application_command_permissions_cleanup(
    struct discord_application_command_permissions *this);

void discord_create_global_application_command_init(
    struct discord_create_global_application_command *this);
void discord_create_global_application_command_cleanup(
    struct discord_create_global_application_command *this);

void discord_edit_global_application_command_init(
    struct discord_edit_global_application_command *this);
void discord_edit_global_application_command_cleanup(
    struct discord_edit_global_application_command *this);

void discord_create_guild_application_command_init(
    struct discord_create_guild_application_command *this);
void discord_create_guild_application_command_cleanup(
    struct discord_create_guild_application_command *this);

void discord_edit_guild_application_command_init(
    struct discord_edit_guild_application_command *this);
void discord_edit_guild_application_command_cleanup(
    struct discord_edit_guild_application_command *this);

void discord_edit_application_command_permissions_init(
    struct discord_edit_application_command_permissions *this);
void discord_edit_application_command_permissions_cleanup(
    struct discord_edit_application_command_permissions *this);

void discord_component_init(struct discord_component *this);
void discord_component_cleanup(struct discord_component *this);

void discord_components_cleanup(struct discord_components *this);

void discord_select_options_cleanup(struct discord_select_options *this);

void discord_interaction_init(struct discord_interaction *this);
void discord_interaction_cleanup(struct discord_interaction *this);

void
discord_interaction_response_init(struct discord_interaction_response *this);
void
discord_interaction_response_cleanup(struct discord_interaction_response *this);

void discord_edit_original_interaction_response_init(
    struct discord_edit_original_interaction_response *this);
void discord_edit_original_interaction_response_cleanup(
    struct discord_edit_original_interaction_response *this);

void discord_create_followup_message_init(
    struct discord_create_followup_message *this);
void discord_create_followup_message_cleanup(
    struct discord_create_followup_message *this);

void
discord_edit_followup_message_init(struct discord_edit_followup_message *this);
void discord_edit_followup_message_cleanup(
    struct discord_edit_followup_message *this);

size_t strings_from_jsmnf(jsmnf *root, const char buf[], struct strings *this);
size_t strings_from_json(const char buf[], size_t size, struct strings *this);

size_t json_values_from_jsmnf(jsmnf *root, const char buf[],
                              struct json_values *this);
size_t json_values_from_json(const char buf[], size_t size,
                             struct json_values *this);

size_t snowflakes_from_jsmnf(jsmnf *root, const char buf[],
                             struct snowflakes *this);
size_t snowflakes_from_json(const char buf[], size_t size,
                            struct snowflakes *this);

size_t integers_from_jsmnf(jsmnf *root, const char buf[],
                           struct integers *this);
size_t integers_from_json(const char buf[], size_t size, struct integers *this);

size_t discord_role_from_jsmnf(jsmnf *root, const char buf[],
                               struct discord_role *this);
size_t discord_role_from_json(const char buf[], size_t size,
                              struct discord_role *this);

size_t discord_roles_from_jsmnf(jsmnf *root, const char buf[],
                                struct discord_roles *this);
size_t discord_roles_from_json(const char buf[], size_t size,
                               struct discord_roles *this);

size_t discord_application_from_jsmnf(jsmnf *root, const char buf[],
                                      struct discord_application *this);
size_t discord_application_from_json(const char buf[], size_t size,
                                     struct discord_application *this);

size_t discord_audit_log_from_jsmnf(jsmnf *root, const char buf[],
                                    struct discord_audit_log *this);
size_t discord_audit_log_from_json(const char buf[], size_t size,
                                   struct discord_audit_log *this);

size_t discord_invite_from_jsmnf(jsmnf *root, const char buf[],
                                 struct discord_invite *this);
size_t discord_invite_from_json(const char buf[], size_t size,
                                struct discord_invite *this);

size_t discord_invites_from_jsmnf(jsmnf *root, const char buf[],
                                  struct discord_invites *this);
size_t discord_invites_from_json(const char buf[], size_t size,
                                 struct discord_invites *this);

size_t discord_get_invite_from_jsmnf(jsmnf *root, const char buf[],
                                     struct discord_get_invite *this);
size_t discord_get_invite_from_json(const char buf[], size_t size,
                                    struct discord_get_invite *this);

size_t discord_channel_from_jsmnf(jsmnf *root, const char buf[],
                                  struct discord_channel *this);
size_t discord_channel_from_json(const char buf[], size_t size,
                                 struct discord_channel *this);

size_t discord_channels_from_jsmnf(jsmnf *root, const char buf[],
                                   struct discord_channels *this);
size_t discord_channels_from_json(const char buf[], size_t size,
                                  struct discord_channels *this);

size_t discord_message_from_jsmnf(jsmnf *root, const char buf[],
                                  struct discord_message *this);
size_t discord_message_from_json(const char buf[], size_t size,
                                 struct discord_message *this);

size_t discord_messages_from_jsmnf(jsmnf *root, const char buf[],
                                   struct discord_messages *this);
size_t discord_messages_from_json(const char buf[], size_t size,
                                  struct discord_messages *this);

size_t
discord_followed_channel_from_jsmnf(jsmnf *root, const char buf[],
                                    struct discord_followed_channel *this);
size_t
discord_followed_channel_from_json(const char buf[], size_t size,
                                   struct discord_followed_channel *this);

size_t discord_thread_members_from_jsmnf(jsmnf *root, const char buf[],
                                         struct discord_thread_members *this);
size_t discord_thread_members_from_json(const char buf[], size_t size,
                                        struct discord_thread_members *this);

size_t discord_attachments_from_jsmnf(jsmnf *root, const char buf[],
                                      struct discord_attachments *this);
size_t discord_attachments_from_json(const char buf[], size_t size,
                                     struct discord_attachments *this);

size_t discord_embed_from_jsmnf(jsmnf *root, const char buf[],
                                struct discord_embed *this);
size_t discord_embed_from_json(const char buf[], size_t size,
                               struct discord_embed *this);

size_t discord_embeds_from_jsmnf(jsmnf *root, const char buf[],
                                 struct discord_embeds *this);
size_t discord_embeds_from_json(const char buf[], size_t size,
                                struct discord_embeds *this);

size_t discord_embed_thumbnail_from_jsmnf(jsmnf *root, const char buf[],
                                          struct discord_embed_thumbnail *this);
size_t discord_embed_thumbnail_from_json(const char buf[], size_t size,
                                         struct discord_embed_thumbnail *this);

size_t discord_embed_video_from_jsmnf(jsmnf *root, const char buf[],
                                      struct discord_embed_video *this);
size_t discord_embed_video_from_json(const char buf[], size_t size,
                                     struct discord_embed_video *this);

size_t discord_embed_image_from_jsmnf(jsmnf *root, const char buf[],
                                      struct discord_embed_image *this);
size_t discord_embed_image_from_json(const char buf[], size_t size,
                                     struct discord_embed_image *this);

size_t discord_embed_provider_from_jsmnf(jsmnf *root, const char buf[],
                                         struct discord_embed_provider *this);
size_t discord_embed_provider_from_json(const char buf[], size_t size,
                                        struct discord_embed_provider *this);

size_t discord_embed_author_from_jsmnf(jsmnf *root, const char buf[],
                                       struct discord_embed_author *this);
size_t discord_embed_author_from_json(const char buf[], size_t size,
                                      struct discord_embed_author *this);

size_t discord_embed_footer_from_jsmnf(jsmnf *root, const char buf[],
                                       struct discord_embed_footer *this);
size_t discord_embed_footer_from_json(const char buf[], size_t size,
                                      struct discord_embed_footer *this);

size_t discord_embed_field_from_jsmnf(jsmnf *root, const char buf[],
                                      struct discord_embed_field *this);
size_t discord_embed_field_from_json(const char buf[], size_t size,
                                     struct discord_embed_field *this);

size_t discord_embed_fields_from_jsmnf(jsmnf *root, const char buf[],
                                       struct discord_embed_fields *this);
size_t discord_embed_fields_from_json(const char buf[], size_t size,
                                      struct discord_embed_fields *this);

size_t discord_thread_response_body_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_thread_response_body *this);
size_t discord_thread_response_body_from_json(
    const char buf[], size_t size, struct discord_thread_response_body *this);

size_t discord_modify_channel_from_jsmnf(jsmnf *root, const char buf[],
                                         struct discord_modify_channel *this);
size_t discord_modify_channel_from_json(const char buf[], size_t size,
                                        struct discord_modify_channel *this);

size_t discord_get_channel_messages_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_get_channel_messages *this);
size_t discord_get_channel_messages_from_json(
    const char buf[], size_t size, struct discord_get_channel_messages *this);

size_t discord_create_message_from_jsmnf(jsmnf *root, const char buf[],
                                         struct discord_create_message *this);
size_t discord_create_message_from_json(const char buf[], size_t size,
                                        struct discord_create_message *this);

size_t discord_get_reactions_from_jsmnf(jsmnf *root, const char buf[],
                                        struct discord_get_reactions *this);
size_t discord_get_reactions_from_json(const char buf[], size_t size,
                                       struct discord_get_reactions *this);

size_t discord_edit_message_from_jsmnf(jsmnf *root, const char buf[],
                                       struct discord_edit_message *this);
size_t discord_edit_message_from_json(const char buf[], size_t size,
                                      struct discord_edit_message *this);

size_t discord_bulk_delete_messages_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_bulk_delete_messages *this);
size_t discord_bulk_delete_messages_from_json(
    const char buf[], size_t size, struct discord_bulk_delete_messages *this);

size_t discord_edit_channel_permissions_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_edit_channel_permissions *this);
size_t discord_edit_channel_permissions_from_json(
    const char buf[], size_t size,
    struct discord_edit_channel_permissions *this);

size_t discord_create_channel_invite_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_create_channel_invite *this);
size_t discord_create_channel_invite_from_json(
    const char buf[], size_t size, struct discord_create_channel_invite *this);

size_t discord_follow_news_channel_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_follow_news_channel *this);
size_t
discord_follow_news_channel_from_json(const char buf[], size_t size,
                                      struct discord_follow_news_channel *this);

size_t discord_group_dm_add_recipient_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_group_dm_add_recipient *this);
size_t discord_group_dm_add_recipient_from_json(
    const char buf[], size_t size, struct discord_group_dm_add_recipient *this);

size_t discord_start_thread_with_message_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_start_thread_with_message *this);
size_t discord_start_thread_with_message_from_json(
    const char buf[], size_t size,
    struct discord_start_thread_with_message *this);

size_t discord_start_thread_without_message_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_start_thread_without_message *this);
size_t discord_start_thread_without_message_from_json(
    const char buf[], size_t size,
    struct discord_start_thread_without_message *this);

size_t discord_list_active_threads_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_list_active_threads *this);
size_t
discord_list_active_threads_from_json(const char buf[], size_t size,
                                      struct discord_list_active_threads *this);

size_t discord_emoji_from_jsmnf(jsmnf *root, const char buf[],
                                struct discord_emoji *this);
size_t discord_emoji_from_json(const char buf[], size_t size,
                               struct discord_emoji *this);

size_t discord_emojis_from_jsmnf(jsmnf *root, const char buf[],
                                 struct discord_emojis *this);
size_t discord_emojis_from_json(const char buf[], size_t size,
                                struct discord_emojis *this);

size_t
discord_create_guild_emoji_from_jsmnf(jsmnf *root, const char buf[],
                                      struct discord_create_guild_emoji *this);
size_t
discord_create_guild_emoji_from_json(const char buf[], size_t size,
                                     struct discord_create_guild_emoji *this);

size_t
discord_modify_guild_emoji_from_jsmnf(jsmnf *root, const char buf[],
                                      struct discord_modify_guild_emoji *this);
size_t
discord_modify_guild_emoji_from_json(const char buf[], size_t size,
                                     struct discord_modify_guild_emoji *this);

size_t discord_guild_from_jsmnf(jsmnf *root, const char buf[],
                                struct discord_guild *this);
size_t discord_guild_from_json(const char buf[], size_t size,
                               struct discord_guild *this);

size_t discord_guilds_from_jsmnf(jsmnf *root, const char buf[],
                                 struct discord_guilds *this);
size_t discord_guilds_from_json(const char buf[], size_t size,
                                struct discord_guilds *this);

size_t discord_guild_preview_from_jsmnf(jsmnf *root, const char buf[],
                                        struct discord_guild_preview *this);
size_t discord_guild_preview_from_json(const char buf[], size_t size,
                                       struct discord_guild_preview *this);

size_t discord_guild_member_from_jsmnf(jsmnf *root, const char buf[],
                                       struct discord_guild_member *this);
size_t discord_guild_member_from_json(const char buf[], size_t size,
                                      struct discord_guild_member *this);

size_t discord_guild_members_from_jsmnf(jsmnf *root, const char buf[],
                                        struct discord_guild_members *this);
size_t discord_guild_members_from_json(const char buf[], size_t size,
                                       struct discord_guild_members *this);

size_t discord_ban_from_jsmnf(jsmnf *root, const char buf[],
                              struct discord_ban *this);
size_t discord_ban_from_json(const char buf[], size_t size,
                             struct discord_ban *this);

size_t discord_bans_from_jsmnf(jsmnf *root, const char buf[],
                               struct discord_bans *this);
size_t discord_bans_from_json(const char buf[], size_t size,
                              struct discord_bans *this);

size_t discord_welcome_screen_from_jsmnf(jsmnf *root, const char buf[],
                                         struct discord_welcome_screen *this);
size_t discord_welcome_screen_from_json(const char buf[], size_t size,
                                        struct discord_welcome_screen *this);

size_t discord_create_guild_from_jsmnf(jsmnf *root, const char buf[],
                                       struct discord_create_guild *this);
size_t discord_create_guild_from_json(const char buf[], size_t size,
                                      struct discord_create_guild *this);

size_t discord_modify_guild_from_jsmnf(jsmnf *root, const char buf[],
                                       struct discord_modify_guild *this);
size_t discord_modify_guild_from_json(const char buf[], size_t size,
                                      struct discord_modify_guild *this);

size_t discord_create_guild_channel_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_create_guild_channel *this);
size_t discord_create_guild_channel_from_json(
    const char buf[], size_t size, struct discord_create_guild_channel *this);

size_t discord_modify_guild_channel_positions_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_modify_guild_channel_positions *this);
size_t discord_modify_guild_channel_positions_from_json(
    const char buf[], size_t size,
    struct discord_modify_guild_channel_positions *this);

size_t discord_list_active_guild_threads_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_list_active_guild_threads *this);
size_t discord_list_active_guild_threads_from_json(
    const char buf[], size_t size,
    struct discord_list_active_guild_threads *this);

size_t
discord_add_guild_member_from_jsmnf(jsmnf *root, const char buf[],
                                    struct discord_add_guild_member *this);
size_t
discord_add_guild_member_from_json(const char buf[], size_t size,
                                   struct discord_add_guild_member *this);

size_t discord_modify_guild_member_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_modify_guild_member *this);
size_t
discord_modify_guild_member_from_json(const char buf[], size_t size,
                                      struct discord_modify_guild_member *this);

size_t discord_modify_current_member_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_modify_current_member *this);
size_t discord_modify_current_member_from_json(
    const char buf[], size_t size, struct discord_modify_current_member *this);

size_t discord_modify_current_user_nick_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_modify_current_user_nick *this);
size_t discord_modify_current_user_nick_from_json(
    const char buf[], size_t size,
    struct discord_modify_current_user_nick *this);

size_t
discord_create_guild_ban_from_jsmnf(jsmnf *root, const char buf[],
                                    struct discord_create_guild_ban *this);
size_t
discord_create_guild_ban_from_json(const char buf[], size_t size,
                                   struct discord_create_guild_ban *this);

size_t
discord_create_guild_role_from_jsmnf(jsmnf *root, const char buf[],
                                     struct discord_create_guild_role *this);
size_t
discord_create_guild_role_from_json(const char buf[], size_t size,
                                    struct discord_create_guild_role *this);

size_t discord_modify_guild_role_positions_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_modify_guild_role_positions *this);
size_t discord_modify_guild_role_positions_from_json(
    const char buf[], size_t size,
    struct discord_modify_guild_role_positions *this);

size_t
discord_modify_guild_role_from_jsmnf(jsmnf *root, const char buf[],
                                     struct discord_modify_guild_role *this);
size_t
discord_modify_guild_role_from_json(const char buf[], size_t size,
                                    struct discord_modify_guild_role *this);

size_t
discord_begin_guild_prune_from_jsmnf(jsmnf *root, const char buf[],
                                     struct discord_begin_guild_prune *this);
size_t
discord_begin_guild_prune_from_json(const char buf[], size_t size,
                                    struct discord_begin_guild_prune *this);

size_t discord_modify_guild_welcome_screen_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_modify_guild_welcome_screen *this);
size_t discord_modify_guild_welcome_screen_from_json(
    const char buf[], size_t size,
    struct discord_modify_guild_welcome_screen *this);

size_t discord_modify_current_user_voice_state_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_modify_current_user_voice_state *this);
size_t discord_modify_current_user_voice_state_from_json(
    const char buf[], size_t size,
    struct discord_modify_current_user_voice_state *this);

size_t discord_modify_user_voice_state_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_modify_user_voice_state *this);
size_t discord_modify_user_voice_state_from_json(
    const char buf[], size_t size,
    struct discord_modify_user_voice_state *this);

size_t discord_guild_scheduled_event_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_guild_scheduled_event *this);
size_t discord_guild_scheduled_event_from_json(
    const char buf[], size_t size, struct discord_guild_scheduled_event *this);

size_t discord_guild_scheduled_events_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_guild_scheduled_events *this);
size_t discord_guild_scheduled_events_from_json(
    const char buf[], size_t size, struct discord_guild_scheduled_events *this);

size_t discord_list_scheduled_events_for_guild_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_list_scheduled_events_for_guild *this);
size_t discord_list_scheduled_events_for_guild_from_json(
    const char buf[], size_t size,
    struct discord_list_scheduled_events_for_guild *this);

size_t discord_create_guild_scheduled_event_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_create_guild_scheduled_event *this);
size_t discord_create_guild_scheduled_event_from_json(
    const char buf[], size_t size,
    struct discord_create_guild_scheduled_event *this);

size_t discord_get_guild_scheduled_event_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_get_guild_scheduled_event *this);
size_t discord_get_guild_scheduled_event_from_json(
    const char buf[], size_t size,
    struct discord_get_guild_scheduled_event *this);

size_t discord_modify_guild_scheduled_event_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_modify_guild_scheduled_event *this);
size_t discord_modify_guild_scheduled_event_from_json(
    const char buf[], size_t size,
    struct discord_modify_guild_scheduled_event *this);

size_t discord_get_guild_scheduled_event_users_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_get_guild_scheduled_event_users *this);
size_t discord_get_guild_scheduled_event_users_from_json(
    const char buf[], size_t size,
    struct discord_get_guild_scheduled_event_users *this);

size_t discord_guild_template_from_jsmnf(jsmnf *root, const char buf[],
                                         struct discord_guild_template *this);
size_t discord_guild_template_from_json(const char buf[], size_t size,
                                        struct discord_guild_template *this);

size_t discord_create_guild_from_guild_template_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_create_guild_from_guild_template *this);
size_t discord_create_guild_from_guild_template_from_json(
    const char buf[], size_t size,
    struct discord_create_guild_from_guild_template *this);

size_t discord_create_guild_template_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_create_guild_template *this);
size_t discord_create_guild_template_from_json(
    const char buf[], size_t size, struct discord_create_guild_template *this);

size_t discord_modify_guild_template_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_modify_guild_template *this);
size_t discord_modify_guild_template_from_json(
    const char buf[], size_t size, struct discord_modify_guild_template *this);

size_t discord_stage_instance_from_jsmnf(jsmnf *root, const char buf[],
                                         struct discord_stage_instance *this);
size_t discord_stage_instance_from_json(const char buf[], size_t size,
                                        struct discord_stage_instance *this);

size_t discord_create_stage_instance_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_create_stage_instance *this);
size_t discord_create_stage_instance_from_json(
    const char buf[], size_t size, struct discord_create_stage_instance *this);

size_t discord_modify_stage_instance_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_modify_stage_instance *this);
size_t discord_modify_stage_instance_from_json(
    const char buf[], size_t size, struct discord_modify_stage_instance *this);

size_t discord_sticker_from_jsmnf(jsmnf *root, const char buf[],
                                  struct discord_sticker *this);
size_t discord_sticker_from_json(const char buf[], size_t size,
                                 struct discord_sticker *this);

size_t discord_modify_guild_sticker_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_modify_guild_sticker *this);
size_t discord_modify_guild_sticker_from_json(
    const char buf[], size_t size, struct discord_modify_guild_sticker *this);

size_t discord_user_from_jsmnf(jsmnf *root, const char buf[],
                               struct discord_user *this);
size_t discord_user_from_json(const char buf[], size_t size,
                              struct discord_user *this);

size_t discord_users_from_jsmnf(jsmnf *root, const char buf[],
                                struct discord_users *this);
size_t discord_users_from_json(const char buf[], size_t size,
                               struct discord_users *this);

size_t discord_connections_from_jsmnf(jsmnf *root, const char buf[],
                                      struct discord_connections *this);
size_t discord_connections_from_json(const char buf[], size_t size,
                                     struct discord_connections *this);

size_t discord_modify_current_user_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_modify_current_user *this);
size_t
discord_modify_current_user_from_json(const char buf[], size_t size,
                                      struct discord_modify_current_user *this);

size_t discord_create_dm_from_jsmnf(jsmnf *root, const char buf[],
                                    struct discord_create_dm *this);
size_t discord_create_dm_from_json(const char buf[], size_t size,
                                   struct discord_create_dm *this);

size_t discord_create_group_dm_from_jsmnf(jsmnf *root, const char buf[],
                                          struct discord_create_group_dm *this);
size_t discord_create_group_dm_from_json(const char buf[], size_t size,
                                         struct discord_create_group_dm *this);

size_t discord_voice_state_from_jsmnf(jsmnf *root, const char buf[],
                                      struct discord_voice_state *this);
size_t discord_voice_state_from_json(const char buf[], size_t size,
                                     struct discord_voice_state *this);

size_t discord_voice_states_from_jsmnf(jsmnf *root, const char buf[],
                                       struct discord_voice_states *this);
size_t discord_voice_states_from_json(const char buf[], size_t size,
                                      struct discord_voice_states *this);

size_t discord_voice_regions_from_jsmnf(jsmnf *root, const char buf[],
                                        struct discord_voice_regions *this);
size_t discord_voice_regions_from_json(const char buf[], size_t size,
                                       struct discord_voice_regions *this);

size_t discord_webhook_from_jsmnf(jsmnf *root, const char buf[],
                                  struct discord_webhook *this);
size_t discord_webhook_from_json(const char buf[], size_t size,
                                 struct discord_webhook *this);

size_t discord_webhooks_from_jsmnf(jsmnf *root, const char buf[],
                                   struct discord_webhooks *this);
size_t discord_webhooks_from_json(const char buf[], size_t size,
                                  struct discord_webhooks *this);

size_t discord_create_webhook_from_jsmnf(jsmnf *root, const char buf[],
                                         struct discord_create_webhook *this);
size_t discord_create_webhook_from_json(const char buf[], size_t size,
                                        struct discord_create_webhook *this);

size_t discord_modify_webhook_from_jsmnf(jsmnf *root, const char buf[],
                                         struct discord_modify_webhook *this);
size_t discord_modify_webhook_from_json(const char buf[], size_t size,
                                        struct discord_modify_webhook *this);

size_t discord_modify_webhook_with_token_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_modify_webhook_with_token *this);
size_t discord_modify_webhook_with_token_from_json(
    const char buf[], size_t size,
    struct discord_modify_webhook_with_token *this);

size_t discord_execute_webhook_from_jsmnf(jsmnf *root, const char buf[],
                                          struct discord_execute_webhook *this);
size_t discord_execute_webhook_from_json(const char buf[], size_t size,
                                         struct discord_execute_webhook *this);

size_t discord_edit_webhook_message_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_edit_webhook_message *this);
size_t discord_edit_webhook_message_from_json(
    const char buf[], size_t size, struct discord_edit_webhook_message *this);

size_t discord_identify_from_jsmnf(jsmnf *root, const char buf[],
                                   struct discord_identify *this);
size_t discord_identify_from_json(const char buf[], size_t size,
                                  struct discord_identify *this);

size_t
discord_voice_state_status_from_jsmnf(jsmnf *root, const char buf[],
                                      struct discord_voice_state_status *this);
size_t
discord_voice_state_status_from_json(const char buf[], size_t size,
                                     struct discord_voice_state_status *this);

size_t discord_presence_update_from_jsmnf(jsmnf *root, const char buf[],
                                          struct discord_presence_update *this);
size_t discord_presence_update_from_json(const char buf[], size_t size,
                                         struct discord_presence_update *this);

size_t discord_session_start_limit_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_session_start_limit *this);
size_t
discord_session_start_limit_from_json(const char buf[], size_t size,
                                      struct discord_session_start_limit *this);

size_t discord_team_from_jsmnf(jsmnf *root, const char buf[],
                               struct discord_team *this);
size_t discord_team_from_json(const char buf[], size_t size,
                              struct discord_team *this);

size_t discord_application_command_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_application_command *this);
size_t
discord_application_command_from_json(const char buf[], size_t size,
                                      struct discord_application_command *this);

size_t discord_application_commands_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_application_commands *this);
size_t discord_application_commands_from_json(
    const char buf[], size_t size, struct discord_application_commands *this);

size_t discord_guild_application_command_permissions_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_guild_application_command_permissions *this);
size_t discord_guild_application_command_permissions_from_json(
    const char buf[], size_t size,
    struct discord_guild_application_command_permissions *this);

size_t discord_application_command_permission_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_application_command_permission *this);
size_t discord_application_command_permission_from_json(
    const char buf[], size_t size,
    struct discord_application_command_permission *this);

size_t discord_application_command_permissions_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_application_command_permissions *this);
size_t discord_application_command_permissions_from_json(
    const char buf[], size_t size,
    struct discord_application_command_permissions *this);

size_t discord_create_global_application_command_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_create_global_application_command *this);
size_t discord_create_global_application_command_from_json(
    const char buf[], size_t size,
    struct discord_create_global_application_command *this);

size_t discord_edit_global_application_command_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_edit_global_application_command *this);
size_t discord_edit_global_application_command_from_json(
    const char buf[], size_t size,
    struct discord_edit_global_application_command *this);

size_t discord_create_guild_application_command_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_create_guild_application_command *this);
size_t discord_create_guild_application_command_from_json(
    const char buf[], size_t size,
    struct discord_create_guild_application_command *this);

size_t discord_edit_guild_application_command_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_edit_guild_application_command *this);
size_t discord_edit_guild_application_command_from_json(
    const char buf[], size_t size,
    struct discord_edit_guild_application_command *this);

size_t discord_edit_application_command_permissions_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_edit_application_command_permissions *this);
size_t discord_edit_application_command_permissions_from_json(
    const char buf[], size_t size,
    struct discord_edit_application_command_permissions *this);

size_t discord_component_from_jsmnf(jsmnf *root, const char buf[],
                                    struct discord_component *this);
size_t discord_component_from_json(const char buf[], size_t size,
                                   struct discord_component *this);

size_t discord_components_from_jsmnf(jsmnf *root, const char buf[],
                                     struct discord_components *this);
size_t discord_components_from_json(const char buf[], size_t size,
                                    struct discord_components *this);

size_t discord_select_options_from_jsmnf(jsmnf *root, const char buf[],
                                         struct discord_select_options *this);
size_t discord_select_options_from_json(const char buf[], size_t size,
                                        struct discord_select_options *this);

size_t discord_interaction_from_jsmnf(jsmnf *root, const char buf[],
                                      struct discord_interaction *this);
size_t discord_interaction_from_json(const char buf[], size_t size,
                                     struct discord_interaction *this);

size_t discord_interaction_response_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_interaction_response *this);
size_t discord_interaction_response_from_json(
    const char buf[], size_t size, struct discord_interaction_response *this);

size_t discord_edit_original_interaction_response_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_edit_original_interaction_response *this);
size_t discord_edit_original_interaction_response_from_json(
    const char buf[], size_t size,
    struct discord_edit_original_interaction_response *this);

size_t discord_create_followup_message_from_jsmnf(
    jsmnf *root, const char buf[],
    struct discord_create_followup_message *this);
size_t discord_create_followup_message_from_json(
    const char buf[], size_t size,
    struct discord_create_followup_message *this);

size_t discord_edit_followup_message_from_jsmnf(
    jsmnf *root, const char buf[], struct discord_edit_followup_message *this);
size_t discord_edit_followup_message_from_json(
    const char buf[], size_t size, struct discord_edit_followup_message *this);

jsonbcode strings_to_jsonb(jsonb *b, char buf[], size_t size,
                           const struct strings *this);
size_t strings_to_json(char buf[], size_t size, const struct strings *this);

jsonbcode json_values_to_jsonb(jsonb *b, char buf[], size_t size,
                               const struct json_values *this);
size_t json_values_to_json(char buf[], size_t size,
                           const struct json_values *this);

jsonbcode snowflakes_to_jsonb(jsonb *b, char buf[], size_t size,
                              const struct snowflakes *this);
size_t snowflakes_to_json(char buf[], size_t size,
                          const struct snowflakes *this);

jsonbcode integers_to_jsonb(jsonb *b, char buf[], size_t size,
                            const struct integers *this);
size_t integers_to_json(char buf[], size_t size, const struct integers *this);

jsonbcode discord_role_to_jsonb(jsonb *b, char buf[], size_t size,
                                const struct discord_role *this);
size_t discord_role_to_json(char buf[], size_t size,
                            const struct discord_role *this);

jsonbcode discord_roles_to_jsonb(jsonb *b, char buf[], size_t size,
                                 const struct discord_roles *this);
size_t discord_roles_to_json(char buf[], size_t size,
                             const struct discord_roles *this);

jsonbcode discord_application_to_jsonb(jsonb *b, char buf[], size_t size,
                                       const struct discord_application *this);
size_t discord_application_to_json(char buf[], size_t size,
                                   const struct discord_application *this);

jsonbcode discord_audit_log_to_jsonb(jsonb *b, char buf[], size_t size,
                                     const struct discord_audit_log *this);
size_t discord_audit_log_to_json(char buf[], size_t size,
                                 const struct discord_audit_log *this);

jsonbcode discord_invite_to_jsonb(jsonb *b, char buf[], size_t size,
                                  const struct discord_invite *this);
size_t discord_invite_to_json(char buf[], size_t size,
                              const struct discord_invite *this);

jsonbcode discord_invites_to_jsonb(jsonb *b, char buf[], size_t size,
                                   const struct discord_invites *this);
size_t discord_invites_to_json(char buf[], size_t size,
                               const struct discord_invites *this);

jsonbcode discord_get_invite_to_jsonb(jsonb *b, char buf[], size_t size,
                                      const struct discord_get_invite *this);
size_t discord_get_invite_to_json(char buf[], size_t size,
                                  const struct discord_get_invite *this);

jsonbcode discord_channel_to_jsonb(jsonb *b, char buf[], size_t size,
                                   const struct discord_channel *this);
size_t discord_channel_to_json(char buf[], size_t size,
                               const struct discord_channel *this);

jsonbcode discord_channels_to_jsonb(jsonb *b, char buf[], size_t size,
                                    const struct discord_channels *this);
size_t discord_channels_to_json(char buf[], size_t size,
                                const struct discord_channels *this);

jsonbcode discord_message_to_jsonb(jsonb *b, char buf[], size_t size,
                                   const struct discord_message *this);
size_t discord_message_to_json(char buf[], size_t size,
                               const struct discord_message *this);

jsonbcode discord_messages_to_jsonb(jsonb *b, char buf[], size_t size,
                                    const struct discord_messages *this);
size_t discord_messages_to_json(char buf[], size_t size,
                                const struct discord_messages *this);

jsonbcode
discord_followed_channel_to_jsonb(jsonb *b, char buf[], size_t size,
                                  const struct discord_followed_channel *this);
size_t
discord_followed_channel_to_json(char buf[], size_t size,
                                 const struct discord_followed_channel *this);

jsonbcode
discord_thread_members_to_jsonb(jsonb *b, char buf[], size_t size,
                                const struct discord_thread_members *this);
size_t
discord_thread_members_to_json(char buf[], size_t size,
                               const struct discord_thread_members *this);

jsonbcode discord_attachments_to_jsonb(jsonb *b, char buf[], size_t size,
                                       const struct discord_attachments *this);
size_t discord_attachments_to_json(char buf[], size_t size,
                                   const struct discord_attachments *this);

jsonbcode discord_embed_to_jsonb(jsonb *b, char buf[], size_t size,
                                 const struct discord_embed *this);
size_t discord_embed_to_json(char buf[], size_t size,
                             const struct discord_embed *this);

jsonbcode discord_embeds_to_jsonb(jsonb *b, char buf[], size_t size,
                                  const struct discord_embeds *this);
size_t discord_embeds_to_json(char buf[], size_t size,
                              const struct discord_embeds *this);

jsonbcode
discord_embed_thumbnail_to_jsonb(jsonb *b, char buf[], size_t size,
                                 const struct discord_embed_thumbnail *this);
size_t
discord_embed_thumbnail_to_json(char buf[], size_t size,
                                const struct discord_embed_thumbnail *this);

jsonbcode discord_embed_video_to_jsonb(jsonb *b, char buf[], size_t size,
                                       const struct discord_embed_video *this);
size_t discord_embed_video_to_json(char buf[], size_t size,
                                   const struct discord_embed_video *this);

jsonbcode discord_embed_image_to_jsonb(jsonb *b, char buf[], size_t size,
                                       const struct discord_embed_image *this);
size_t discord_embed_image_to_json(char buf[], size_t size,
                                   const struct discord_embed_image *this);

jsonbcode
discord_embed_provider_to_jsonb(jsonb *b, char buf[], size_t size,
                                const struct discord_embed_provider *this);
size_t
discord_embed_provider_to_json(char buf[], size_t size,
                               const struct discord_embed_provider *this);

jsonbcode
discord_embed_author_to_jsonb(jsonb *b, char buf[], size_t size,
                              const struct discord_embed_author *this);
size_t discord_embed_author_to_json(char buf[], size_t size,
                                    const struct discord_embed_author *this);

jsonbcode
discord_embed_footer_to_jsonb(jsonb *b, char buf[], size_t size,
                              const struct discord_embed_footer *this);
size_t discord_embed_footer_to_json(char buf[], size_t size,
                                    const struct discord_embed_footer *this);

jsonbcode discord_embed_field_to_jsonb(jsonb *b, char buf[], size_t size,
                                       const struct discord_embed_field *this);
size_t discord_embed_field_to_json(char buf[], size_t size,
                                   const struct discord_embed_field *this);

jsonbcode
discord_embed_fields_to_jsonb(jsonb *b, char buf[], size_t size,
                              const struct discord_embed_fields *this);
size_t discord_embed_fields_to_json(char buf[], size_t size,
                                    const struct discord_embed_fields *this);

jsonbcode discord_thread_response_body_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_thread_response_body *this);
size_t discord_thread_response_body_to_json(
    char buf[], size_t size, const struct discord_thread_response_body *this);

jsonbcode
discord_modify_channel_to_jsonb(jsonb *b, char buf[], size_t size,
                                const struct discord_modify_channel *this);
size_t
discord_modify_channel_to_json(char buf[], size_t size,
                               const struct discord_modify_channel *this);

jsonbcode discord_get_channel_messages_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_get_channel_messages *this);
size_t discord_get_channel_messages_to_json(
    char buf[], size_t size, const struct discord_get_channel_messages *this);

jsonbcode
discord_create_message_to_jsonb(jsonb *b, char buf[], size_t size,
                                const struct discord_create_message *this);
size_t
discord_create_message_to_json(char buf[], size_t size,
                               const struct discord_create_message *this);

jsonbcode
discord_get_reactions_to_jsonb(jsonb *b, char buf[], size_t size,
                               const struct discord_get_reactions *this);
size_t discord_get_reactions_to_json(char buf[], size_t size,
                                     const struct discord_get_reactions *this);

jsonbcode
discord_edit_message_to_jsonb(jsonb *b, char buf[], size_t size,
                              const struct discord_edit_message *this);
size_t discord_edit_message_to_json(char buf[], size_t size,
                                    const struct discord_edit_message *this);

jsonbcode discord_bulk_delete_messages_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_bulk_delete_messages *this);
size_t discord_bulk_delete_messages_to_json(
    char buf[], size_t size, const struct discord_bulk_delete_messages *this);

jsonbcode discord_edit_channel_permissions_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_edit_channel_permissions *this);
size_t discord_edit_channel_permissions_to_json(
    char buf[], size_t size,
    const struct discord_edit_channel_permissions *this);

jsonbcode discord_create_channel_invite_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_create_channel_invite *this);
size_t discord_create_channel_invite_to_json(
    char buf[], size_t size, const struct discord_create_channel_invite *this);

jsonbcode discord_follow_news_channel_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_follow_news_channel *this);
size_t discord_follow_news_channel_to_json(
    char buf[], size_t size, const struct discord_follow_news_channel *this);

jsonbcode discord_group_dm_add_recipient_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_group_dm_add_recipient *this);
size_t discord_group_dm_add_recipient_to_json(
    char buf[], size_t size, const struct discord_group_dm_add_recipient *this);

jsonbcode discord_start_thread_with_message_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_start_thread_with_message *this);
size_t discord_start_thread_with_message_to_json(
    char buf[], size_t size,
    const struct discord_start_thread_with_message *this);

jsonbcode discord_start_thread_without_message_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_start_thread_without_message *this);
size_t discord_start_thread_without_message_to_json(
    char buf[], size_t size,
    const struct discord_start_thread_without_message *this);

jsonbcode discord_list_active_threads_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_list_active_threads *this);
size_t discord_list_active_threads_to_json(
    char buf[], size_t size, const struct discord_list_active_threads *this);

jsonbcode discord_emoji_to_jsonb(jsonb *b, char buf[], size_t size,
                                 const struct discord_emoji *this);
size_t discord_emoji_to_json(char buf[], size_t size,
                             const struct discord_emoji *this);

jsonbcode discord_emojis_to_jsonb(jsonb *b, char buf[], size_t size,
                                  const struct discord_emojis *this);
size_t discord_emojis_to_json(char buf[], size_t size,
                              const struct discord_emojis *this);

jsonbcode discord_create_guild_emoji_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_create_guild_emoji *this);
size_t discord_create_guild_emoji_to_json(
    char buf[], size_t size, const struct discord_create_guild_emoji *this);

jsonbcode discord_modify_guild_emoji_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_modify_guild_emoji *this);
size_t discord_modify_guild_emoji_to_json(
    char buf[], size_t size, const struct discord_modify_guild_emoji *this);

jsonbcode discord_guild_to_jsonb(jsonb *b, char buf[], size_t size,
                                 const struct discord_guild *this);
size_t discord_guild_to_json(char buf[], size_t size,
                             const struct discord_guild *this);

jsonbcode discord_guilds_to_jsonb(jsonb *b, char buf[], size_t size,
                                  const struct discord_guilds *this);
size_t discord_guilds_to_json(char buf[], size_t size,
                              const struct discord_guilds *this);

jsonbcode
discord_guild_preview_to_jsonb(jsonb *b, char buf[], size_t size,
                               const struct discord_guild_preview *this);
size_t discord_guild_preview_to_json(char buf[], size_t size,
                                     const struct discord_guild_preview *this);

jsonbcode
discord_guild_member_to_jsonb(jsonb *b, char buf[], size_t size,
                              const struct discord_guild_member *this);
size_t discord_guild_member_to_json(char buf[], size_t size,
                                    const struct discord_guild_member *this);

jsonbcode
discord_guild_members_to_jsonb(jsonb *b, char buf[], size_t size,
                               const struct discord_guild_members *this);
size_t discord_guild_members_to_json(char buf[], size_t size,
                                     const struct discord_guild_members *this);

jsonbcode discord_ban_to_jsonb(jsonb *b, char buf[], size_t size,
                               const struct discord_ban *this);
size_t discord_ban_to_json(char buf[], size_t size,
                           const struct discord_ban *this);

jsonbcode discord_bans_to_jsonb(jsonb *b, char buf[], size_t size,
                                const struct discord_bans *this);
size_t discord_bans_to_json(char buf[], size_t size,
                            const struct discord_bans *this);

jsonbcode
discord_welcome_screen_to_jsonb(jsonb *b, char buf[], size_t size,
                                const struct discord_welcome_screen *this);
size_t
discord_welcome_screen_to_json(char buf[], size_t size,
                               const struct discord_welcome_screen *this);

jsonbcode
discord_create_guild_to_jsonb(jsonb *b, char buf[], size_t size,
                              const struct discord_create_guild *this);
size_t discord_create_guild_to_json(char buf[], size_t size,
                                    const struct discord_create_guild *this);

jsonbcode
discord_modify_guild_to_jsonb(jsonb *b, char buf[], size_t size,
                              const struct discord_modify_guild *this);
size_t discord_modify_guild_to_json(char buf[], size_t size,
                                    const struct discord_modify_guild *this);

jsonbcode discord_create_guild_channel_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_create_guild_channel *this);
size_t discord_create_guild_channel_to_json(
    char buf[], size_t size, const struct discord_create_guild_channel *this);

jsonbcode discord_modify_guild_channel_positions_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_modify_guild_channel_positions *this);
size_t discord_modify_guild_channel_positions_to_json(
    char buf[], size_t size,
    const struct discord_modify_guild_channel_positions *this);

jsonbcode discord_list_active_guild_threads_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_list_active_guild_threads *this);
size_t discord_list_active_guild_threads_to_json(
    char buf[], size_t size,
    const struct discord_list_active_guild_threads *this);

jsonbcode
discord_add_guild_member_to_jsonb(jsonb *b, char buf[], size_t size,
                                  const struct discord_add_guild_member *this);
size_t
discord_add_guild_member_to_json(char buf[], size_t size,
                                 const struct discord_add_guild_member *this);

jsonbcode discord_modify_guild_member_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_modify_guild_member *this);
size_t discord_modify_guild_member_to_json(
    char buf[], size_t size, const struct discord_modify_guild_member *this);

jsonbcode discord_modify_current_member_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_modify_current_member *this);
size_t discord_modify_current_member_to_json(
    char buf[], size_t size, const struct discord_modify_current_member *this);

jsonbcode discord_modify_current_user_nick_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_modify_current_user_nick *this);
size_t discord_modify_current_user_nick_to_json(
    char buf[], size_t size,
    const struct discord_modify_current_user_nick *this);

jsonbcode
discord_create_guild_ban_to_jsonb(jsonb *b, char buf[], size_t size,
                                  const struct discord_create_guild_ban *this);
size_t
discord_create_guild_ban_to_json(char buf[], size_t size,
                                 const struct discord_create_guild_ban *this);

jsonbcode discord_create_guild_role_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_create_guild_role *this);
size_t
discord_create_guild_role_to_json(char buf[], size_t size,
                                  const struct discord_create_guild_role *this);

jsonbcode discord_modify_guild_role_positions_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_modify_guild_role_positions *this);
size_t discord_modify_guild_role_positions_to_json(
    char buf[], size_t size,
    const struct discord_modify_guild_role_positions *this);

jsonbcode discord_modify_guild_role_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_modify_guild_role *this);
size_t
discord_modify_guild_role_to_json(char buf[], size_t size,
                                  const struct discord_modify_guild_role *this);

jsonbcode discord_begin_guild_prune_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_begin_guild_prune *this);
size_t
discord_begin_guild_prune_to_json(char buf[], size_t size,
                                  const struct discord_begin_guild_prune *this);

jsonbcode discord_modify_guild_welcome_screen_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_modify_guild_welcome_screen *this);
size_t discord_modify_guild_welcome_screen_to_json(
    char buf[], size_t size,
    const struct discord_modify_guild_welcome_screen *this);

jsonbcode discord_modify_current_user_voice_state_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_modify_current_user_voice_state *this);
size_t discord_modify_current_user_voice_state_to_json(
    char buf[], size_t size,
    const struct discord_modify_current_user_voice_state *this);

jsonbcode discord_modify_user_voice_state_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_modify_user_voice_state *this);
size_t discord_modify_user_voice_state_to_json(
    char buf[], size_t size,
    const struct discord_modify_user_voice_state *this);

jsonbcode discord_guild_scheduled_event_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_guild_scheduled_event *this);
size_t discord_guild_scheduled_event_to_json(
    char buf[], size_t size, const struct discord_guild_scheduled_event *this);

jsonbcode discord_guild_scheduled_events_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_guild_scheduled_events *this);
size_t discord_guild_scheduled_events_to_json(
    char buf[], size_t size, const struct discord_guild_scheduled_events *this);

jsonbcode discord_list_scheduled_events_for_guild_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_list_scheduled_events_for_guild *this);
size_t discord_list_scheduled_events_for_guild_to_json(
    char buf[], size_t size,
    const struct discord_list_scheduled_events_for_guild *this);

jsonbcode discord_create_guild_scheduled_event_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_create_guild_scheduled_event *this);
size_t discord_create_guild_scheduled_event_to_json(
    char buf[], size_t size,
    const struct discord_create_guild_scheduled_event *this);

jsonbcode discord_get_guild_scheduled_event_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_get_guild_scheduled_event *this);
size_t discord_get_guild_scheduled_event_to_json(
    char buf[], size_t size,
    const struct discord_get_guild_scheduled_event *this);

jsonbcode discord_modify_guild_scheduled_event_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_modify_guild_scheduled_event *this);
size_t discord_modify_guild_scheduled_event_to_json(
    char buf[], size_t size,
    const struct discord_modify_guild_scheduled_event *this);

jsonbcode discord_get_guild_scheduled_event_users_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_get_guild_scheduled_event_users *this);
size_t discord_get_guild_scheduled_event_users_to_json(
    char buf[], size_t size,
    const struct discord_get_guild_scheduled_event_users *this);

jsonbcode
discord_guild_template_to_jsonb(jsonb *b, char buf[], size_t size,
                                const struct discord_guild_template *this);
size_t
discord_guild_template_to_json(char buf[], size_t size,
                               const struct discord_guild_template *this);

jsonbcode discord_create_guild_from_guild_template_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_create_guild_from_guild_template *this);
size_t discord_create_guild_from_guild_template_to_json(
    char buf[], size_t size,
    const struct discord_create_guild_from_guild_template *this);

jsonbcode discord_create_guild_template_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_create_guild_template *this);
size_t discord_create_guild_template_to_json(
    char buf[], size_t size, const struct discord_create_guild_template *this);

jsonbcode discord_modify_guild_template_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_modify_guild_template *this);
size_t discord_modify_guild_template_to_json(
    char buf[], size_t size, const struct discord_modify_guild_template *this);

jsonbcode
discord_stage_instance_to_jsonb(jsonb *b, char buf[], size_t size,
                                const struct discord_stage_instance *this);
size_t
discord_stage_instance_to_json(char buf[], size_t size,
                               const struct discord_stage_instance *this);

jsonbcode discord_create_stage_instance_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_create_stage_instance *this);
size_t discord_create_stage_instance_to_json(
    char buf[], size_t size, const struct discord_create_stage_instance *this);

jsonbcode discord_modify_stage_instance_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_modify_stage_instance *this);
size_t discord_modify_stage_instance_to_json(
    char buf[], size_t size, const struct discord_modify_stage_instance *this);

jsonbcode discord_sticker_to_jsonb(jsonb *b, char buf[], size_t size,
                                   const struct discord_sticker *this);
size_t discord_sticker_to_json(char buf[], size_t size,
                               const struct discord_sticker *this);

jsonbcode discord_modify_guild_sticker_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_modify_guild_sticker *this);
size_t discord_modify_guild_sticker_to_json(
    char buf[], size_t size, const struct discord_modify_guild_sticker *this);

jsonbcode discord_user_to_jsonb(jsonb *b, char buf[], size_t size,
                                const struct discord_user *this);
size_t discord_user_to_json(char buf[], size_t size,
                            const struct discord_user *this);

jsonbcode discord_users_to_jsonb(jsonb *b, char buf[], size_t size,
                                 const struct discord_users *this);
size_t discord_users_to_json(char buf[], size_t size,
                             const struct discord_users *this);

jsonbcode discord_connections_to_jsonb(jsonb *b, char buf[], size_t size,
                                       const struct discord_connections *this);
size_t discord_connections_to_json(char buf[], size_t size,
                                   const struct discord_connections *this);

jsonbcode discord_modify_current_user_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_modify_current_user *this);
size_t discord_modify_current_user_to_json(
    char buf[], size_t size, const struct discord_modify_current_user *this);

jsonbcode discord_create_dm_to_jsonb(jsonb *b, char buf[], size_t size,
                                     const struct discord_create_dm *this);
size_t discord_create_dm_to_json(char buf[], size_t size,
                                 const struct discord_create_dm *this);

jsonbcode
discord_create_group_dm_to_jsonb(jsonb *b, char buf[], size_t size,
                                 const struct discord_create_group_dm *this);
size_t
discord_create_group_dm_to_json(char buf[], size_t size,
                                const struct discord_create_group_dm *this);

jsonbcode discord_voice_state_to_jsonb(jsonb *b, char buf[], size_t size,
                                       const struct discord_voice_state *this);
size_t discord_voice_state_to_json(char buf[], size_t size,
                                   const struct discord_voice_state *this);

jsonbcode
discord_voice_states_to_jsonb(jsonb *b, char buf[], size_t size,
                              const struct discord_voice_states *this);
size_t discord_voice_states_to_json(char buf[], size_t size,
                                    const struct discord_voice_states *this);

jsonbcode
discord_voice_regions_to_jsonb(jsonb *b, char buf[], size_t size,
                               const struct discord_voice_regions *this);
size_t discord_voice_regions_to_json(char buf[], size_t size,
                                     const struct discord_voice_regions *this);

jsonbcode discord_webhook_to_jsonb(jsonb *b, char buf[], size_t size,
                                   const struct discord_webhook *this);
size_t discord_webhook_to_json(char buf[], size_t size,
                               const struct discord_webhook *this);

jsonbcode discord_webhooks_to_jsonb(jsonb *b, char buf[], size_t size,
                                    const struct discord_webhooks *this);
size_t discord_webhooks_to_json(char buf[], size_t size,
                                const struct discord_webhooks *this);

jsonbcode
discord_create_webhook_to_jsonb(jsonb *b, char buf[], size_t size,
                                const struct discord_create_webhook *this);
size_t
discord_create_webhook_to_json(char buf[], size_t size,
                               const struct discord_create_webhook *this);

jsonbcode
discord_modify_webhook_to_jsonb(jsonb *b, char buf[], size_t size,
                                const struct discord_modify_webhook *this);
size_t
discord_modify_webhook_to_json(char buf[], size_t size,
                               const struct discord_modify_webhook *this);

jsonbcode discord_modify_webhook_with_token_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_modify_webhook_with_token *this);
size_t discord_modify_webhook_with_token_to_json(
    char buf[], size_t size,
    const struct discord_modify_webhook_with_token *this);

jsonbcode
discord_execute_webhook_to_jsonb(jsonb *b, char buf[], size_t size,
                                 const struct discord_execute_webhook *this);
size_t
discord_execute_webhook_to_json(char buf[], size_t size,
                                const struct discord_execute_webhook *this);

jsonbcode discord_edit_webhook_message_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_edit_webhook_message *this);
size_t discord_edit_webhook_message_to_json(
    char buf[], size_t size, const struct discord_edit_webhook_message *this);

jsonbcode discord_identify_to_jsonb(jsonb *b, char buf[], size_t size,
                                    const struct discord_identify *this);
size_t discord_identify_to_json(char buf[], size_t size,
                                const struct discord_identify *this);

jsonbcode discord_voice_state_status_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_voice_state_status *this);
size_t discord_voice_state_status_to_json(
    char buf[], size_t size, const struct discord_voice_state_status *this);

jsonbcode
discord_presence_update_to_jsonb(jsonb *b, char buf[], size_t size,
                                 const struct discord_presence_update *this);
size_t
discord_presence_update_to_json(char buf[], size_t size,
                                const struct discord_presence_update *this);

jsonbcode discord_session_start_limit_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_session_start_limit *this);
size_t discord_session_start_limit_to_json(
    char buf[], size_t size, const struct discord_session_start_limit *this);

jsonbcode discord_team_to_jsonb(jsonb *b, char buf[], size_t size,
                                const struct discord_team *this);
size_t discord_team_to_json(char buf[], size_t size,
                            const struct discord_team *this);

jsonbcode discord_application_command_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_application_command *this);
size_t discord_application_command_to_json(
    char buf[], size_t size, const struct discord_application_command *this);

jsonbcode discord_application_commands_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_application_commands *this);
size_t discord_application_commands_to_json(
    char buf[], size_t size, const struct discord_application_commands *this);

jsonbcode discord_guild_application_command_permissions_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_guild_application_command_permissions *this);
size_t discord_guild_application_command_permissions_to_json(
    char buf[], size_t size,
    const struct discord_guild_application_command_permissions *this);

jsonbcode discord_application_command_permission_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_application_command_permission *this);
size_t discord_application_command_permission_to_json(
    char buf[], size_t size,
    const struct discord_application_command_permission *this);

jsonbcode discord_application_command_permissions_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_application_command_permissions *this);
size_t discord_application_command_permissions_to_json(
    char buf[], size_t size,
    const struct discord_application_command_permissions *this);

jsonbcode discord_create_global_application_command_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_create_global_application_command *this);
size_t discord_create_global_application_command_to_json(
    char buf[], size_t size,
    const struct discord_create_global_application_command *this);

jsonbcode discord_edit_global_application_command_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_edit_global_application_command *this);
size_t discord_edit_global_application_command_to_json(
    char buf[], size_t size,
    const struct discord_edit_global_application_command *this);

jsonbcode discord_create_guild_application_command_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_create_guild_application_command *this);
size_t discord_create_guild_application_command_to_json(
    char buf[], size_t size,
    const struct discord_create_guild_application_command *this);

jsonbcode discord_edit_guild_application_command_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_edit_guild_application_command *this);
size_t discord_edit_guild_application_command_to_json(
    char buf[], size_t size,
    const struct discord_edit_guild_application_command *this);

jsonbcode discord_edit_application_command_permissions_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_edit_application_command_permissions *this);
size_t discord_edit_application_command_permissions_to_json(
    char buf[], size_t size,
    const struct discord_edit_application_command_permissions *this);

jsonbcode discord_component_to_jsonb(jsonb *b, char buf[], size_t size,
                                     const struct discord_component *this);
size_t discord_component_to_json(char buf[], size_t size,
                                 const struct discord_component *this);

jsonbcode discord_components_to_jsonb(jsonb *b, char buf[], size_t size,
                                      const struct discord_components *this);
size_t discord_components_to_json(char buf[], size_t size,
                                  const struct discord_components *this);

jsonbcode
discord_select_options_to_jsonb(jsonb *b, char buf[], size_t size,
                                const struct discord_select_options *this);
size_t
discord_select_options_to_json(char buf[], size_t size,
                               const struct discord_select_options *this);

jsonbcode discord_interaction_to_jsonb(jsonb *b, char buf[], size_t size,
                                       const struct discord_interaction *this);
size_t discord_interaction_to_json(char buf[], size_t size,
                                   const struct discord_interaction *this);

jsonbcode discord_interaction_response_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_interaction_response *this);
size_t discord_interaction_response_to_json(
    char buf[], size_t size, const struct discord_interaction_response *this);

jsonbcode discord_edit_original_interaction_response_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_edit_original_interaction_response *this);
size_t discord_edit_original_interaction_response_to_json(
    char buf[], size_t size,
    const struct discord_edit_original_interaction_response *this);

jsonbcode discord_create_followup_message_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_create_followup_message *this);
size_t discord_create_followup_message_to_json(
    char buf[], size_t size,
    const struct discord_create_followup_message *this);

jsonbcode discord_edit_followup_message_to_jsonb(
    jsonb *b, char buf[], size_t size,
    const struct discord_edit_followup_message *this);
size_t discord_edit_followup_message_to_json(
    char buf[], size_t size, const struct discord_edit_followup_message *this);

#endif /* DISCORD_CODECS_H */
