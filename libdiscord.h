#ifndef LIBDISCORD_H_
#define LIBDISCORD_H_

/* This is the version number of the package from which this header
 *  file originates */
#define LIBDISCORD_VERSION "0.0.0-DEV"

/* The numeric version number is also available "in parts" by using
 *  these defines: */
#define LIBDISCORD_VERSION_MAJOR 0
#define LIBDISCORD_VERSION_MINOR 0
#define LIBDISCORD_VERSION_PATCH 0


//forward declaration. see discord-common.h for full definition
typedef struct discord_s discord_t;

enum discord_limits {
  MAX_NAME_LEN           = 100,
  MAX_TOPIC_LEN          = 1024,
  MAX_DESCRIPTION_LEN    = 1024,
  MAX_USERNAME_LEN       = 32,
  MAX_DISCRIMINATOR_LEN  = 10,
  MAX_HASH_LEN           = 1024,
  MAX_LOCALE_LEN         = 15,
  MAX_EMAIL_LEN          = 254,
  MAX_REGION_LEN         = 15,
  MAX_HEADER_LEN         = 512,
  MAX_URL_LEN            = 512,
  MAX_MESSAGE_LEN        = 2048,
  MAX_PAYLOAD_LEN        = 4096,
};

/* SNOWFLAKES
https://discord.com/developers/docs/reference#snowflakes */
enum discord_snowflake {
  SNOWFLAKE_INCREMENT           = 12,
  SNOWFLAKE_PROCESS_ID          = 17,
  SNOWFLAKE_INTERNAL_WORKER_ID  = 22,
  SNOWFLAKE_TIMESTAMP           = 64,
};

/* CHANNEL TYPES
 * https://discord.com/developers/docs/resources/channel#channel-object-channel-types */
enum discord_channel_types {
  GUILD_TEXT      = 0,
  DM              = 1,
  GUILD_VOICE     = 2,
  GROUP_DM        = 3,
  GUILD_CATEGORY  = 4,
  GUILD_NEWS      = 5,
  GUILD_STORE     = 6,
};

/* CHANNEL OBJECT
 * https://discord.com/developers/docs/resources/channel#channel-object-channel-structure */
typedef struct discord_channel_s {
  char id[SNOWFLAKE_INTERNAL_WORKER_ID];
  int type;
  char guild_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  int position;
  //struct discord_overwrite_s **permission_overwrites;
  char name[MAX_NAME_LEN];
  char topic[MAX_TOPIC_LEN];
  _Bool nsfw;
  char last_message_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  int bitrate;
  int user_limit;
  int rate_limit_per_user;
  struct discord_user_s **recipients;
  char icon[MAX_HASH_LEN];
  char owner_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  char application_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  char parent_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  char last_pin_timestamp[SNOWFLAKE_TIMESTAMP];
  struct discord_message_s **messages;
} discord_channel_t;

/* DISCORD MESSAGE OBJECT
 * https://discord.com/developers/docs/resources/channel#message-object*/
typedef struct discord_message_s {
  char id[SNOWFLAKE_INTERNAL_WORKER_ID];
  char channel_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  char guild_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  struct discord_user_s *author;
  //struct discord_guildmember_s *member;
  char content[MAX_MESSAGE_LEN];
  char timestamp[SNOWFLAKE_TIMESTAMP];
  char edited_timestamp[SNOWFLAKE_TIMESTAMP];
  _Bool tts;
  _Bool mention_everyone;
  struct discord_user_s **mentions;
  //struct discord_role_t **mention_roles;
  //struct discord_channelmention_s **mention_channels;
  //struct discord_attachment_s **attachments;
  //struct discord_embed_s **embeds;
  //strict discord_reaction_s **reactions;
  char nonce[SNOWFLAKE_INTERNAL_WORKER_ID];
  _Bool pinned;
  char webhook_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  int type;
  //struct discord_messageactivity_s *activity;
  //struct discord_messageapplication_s *application;
  //struct discord_messagereference_s *message_reference;
  int flags;
  //struct discord_sticker_s **stickers;
  struct discord_message_s *referenced_message;
} discord_message_t;

/* GUILD OBJECT
 * https://discord.com/developers/docs/resources/guild#guild-object-guild-structure */
typedef struct discord_guild_s {
  char id[SNOWFLAKE_INTERNAL_WORKER_ID];
  char name[MAX_NAME_LEN];
  char icon[MAX_HASH_LEN];
  char splash[MAX_HASH_LEN];
  char discovery_splash[MAX_HASH_LEN];
  _Bool owner;
  char owner_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  int permissions;
  char permissions_new[SNOWFLAKE_INCREMENT];
  char region[MAX_REGION_LEN];
  char afk_channel_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  int afk_timeout;
  _Bool embed_enabled;
  char embed_channel_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  int verification_level;
  int default_message_notifications;
  int explicit_content_filter;
  //struct discord_role_t **roles;
  //struct discord_emoji_t **emojis;
  char **features;
  int mfa_level;
  char application_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  _Bool widget_enabled;
  char widget_channel_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  char system_channel_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  int system_channel_flags;
  char rules_channel_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  char joined_at[SNOWFLAKE_TIMESTAMP];
  _Bool large;
  _Bool unavailable;
  int member_count;
  //struct discord_voicestate_s **voice_states;
  //struct discord_member_s **members;
  struct discord_channel_s **channels;
  //struct discord_presence_s **presences;
  int max_presences;
  int mas_members;
  char vanity_url_code[SNOWFLAKE_INCREMENT];
  char description[MAX_DESCRIPTION_LEN];
  char banner[MAX_HASH_LEN];
  int premium_tier;
  int premium_subscription_count;
  char preferred_locale[MAX_LOCALE_LEN];
  char public_updates_channel_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  int max_video_channel_users;
  int approximate_member_count;
  int approximate_presence_count;
} discord_guild_t;

/* USER OBJECT
 * https://discord.com/developers/docs/resources/user#user-object-user-structure */
typedef struct discord_user_s {
  char id[SNOWFLAKE_INTERNAL_WORKER_ID];
  char username[MAX_USERNAME_LEN];
  char discriminator[MAX_DISCRIMINATOR_LEN];
  char avatar[MAX_HASH_LEN];
  _Bool bot;
  _Bool sys;
  _Bool mfa_enabled;
  char locale[MAX_LOCALE_LEN];
  _Bool verified;
  char email[MAX_EMAIL_LEN];
  int flags;
  int premium_type;
  int public_flags;
  struct discord_guild_s **guilds;
} discord_user_t;

typedef void (discord_idle_cb)(discord_t *client, const discord_user_t *self);
typedef void (discord_message_cb)(discord_t *client, const discord_user_t *self, const discord_message_t *message);

/* discord-public.c */

void discord_global_init();
void discord_global_cleanup();

discord_t* discord_init(char token[]);
void discord_cleanup(discord_t *client);

void discord_setcb_idle(discord_t *client, discord_idle_cb *user_cb);
void discord_setcb_ready(discord_t *client, discord_idle_cb *user_cb);
void discord_setcb_message_create(discord_t *client, discord_message_cb *user_cb);
void discord_setcb_message_update(discord_t *client, discord_message_cb *user_cb);
void discord_setcb_message_delete(discord_t *client, discord_message_cb *user_cb);

void discord_run(discord_t *client);

void discord_dump_json(discord_t *client, char file[]);

/* discord-public-guild.c */

discord_guild_t* discord_guild_init();
void discord_guild_cleanup(discord_guild_t *guild);
void discord_get_guild(discord_t *client, char guild_id[], discord_guild_t *p_guild);

/* discord-public-user.c */

discord_user_t* discord_user_init();
void discord_user_cleanup(discord_user_t *user);
void discord_get_user(discord_t *client, char user_id[], discord_user_t *p_user);
void discord_get_client_user(discord_t *client, discord_user_t *p_user);

/* discord-public-message.c */

discord_message_t* discord_message_init();
void discord_message_cleanup(discord_message_t *message);
void discord_send_message(discord_t *client, const char channel_id[], const char content[]);

#endif
