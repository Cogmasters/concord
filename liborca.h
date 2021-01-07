#ifndef LIBORCA_H_
#define LIBORCA_H_

/* This is the version number of the package from which this header
 *  file originates */
#define LIBORCA_VERSION "0.0.0-DEV"

/* The numeric version number is also available "in parts" by using
 *  these defines: */
#define LIBORCA_VERSION_MAJOR 0
#define LIBORCA_VERSION_MINOR 0
#define LIBORCA_VERSION_PATCH 0

//discord events that can be triggered and have callbacks set by users
enum orca_events {
  ON_READY,
  ON_MESSAGE,
};

//forward declaration. see orca-common.h for full definition
typedef struct orca_s orca_t;
//
//function template for user specified websocket callbacks
typedef void (orca_ws_cb)(orca_t *client);


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
typedef struct orca_channel_s {
  char *id;
  int type;
  char *guild_id;
  int position;
  //struct orca_overwrite_s **permission_overwrites;
  char *name;
  char *topic;
  _Bool nsfw;
  char *last_message_id;
  int bitrate;
  int user_limit;
  int rate_limit_per_user;
  struct orca_user_s **recipients;
  char *icon;
  char *owner_id;
  char *application_id;
  char *parent_id;
  char *last_pin_timestamp;
  //struct orca_message_s **messages;
} orca_channel_t;

/* GUILD OBJECT
 * https://discord.com/developers/docs/resources/guild#guild-object-guild-structure */
typedef struct orca_guild_s {
  char *id;
  char *name;
  char *icon;
  char *splash;
  char *discovery_splash;
  _Bool owner;
  char *owner_id;
  int permissions;
  char *permissions_new;
  char *region;
  char *afk_channel_id;
  int afk_timeout;
  _Bool embed_enabled;
  char *embed_channel_id;
  int verification_level;
  int default_message_notifications;
  int explicit_content_filter;
  //struct orca_role_t **roles;
  //struct orca_emoji_t **emojis;
  char **features;
  int mfa_level;
  char *application_id;
  _Bool widget_enabled;
  char *widget_channel_id;
  char *system_channel_id;
  int system_channel_flags;
  char *rules_channel_id;
  char *joined_at;
  _Bool large;
  _Bool unavailable;
  int member_count;
  //struct orca_voicestate_s **voice_states;
  //struct orca_member_s **members;
  struct orca_channel_s **channels;
  //struct orca_presence_s **presences;
  int max_presences;
  int mas_members;
  char *vanity_url_code;
  char *description;
  char *banner;
  int premium_tier;
  int premium_subscription_count;
  char *preferred_locale;
  char *public_updates_channel_id;
  int max_video_channel_users;
  int approximate_member_count;
  int approximate_presence_count;
} orca_guild_t;

/* USER OBJECT
 * https://discord.com/developers/docs/resources/user#user-object-user-structure */
typedef struct orca_user_s {
  char *id;
  char *username;
  char *discriminator;
  char *avatar;
  _Bool bot;
  _Bool sys;
  _Bool mfa_enabled;
  char *locale;
  _Bool verified;
  char *email;
  int flags;
  int premium_type;
  int public_flags;
  struct orca_guild_s **guilds;
} orca_user_t;


/* orca-public.c */

void orca_global_init();
void orca_global_cleanup();

orca_t* orca_init(char token[]);
void orca_cleanup(orca_t *client);

void orca_set_callback(
  orca_t *client, 
  enum orca_events event,
  orca_ws_cb *user_callback);

void orca_connect(orca_t *client);

/* orca-public-guild.c */

orca_guild_t* orca_guild_init();
void orca_guild_cleanup(orca_guild_t *guild);
void orca_get_guild(orca_t *client, char guild_id[], orca_guild_t **p_guild);

/* orca-public-user.c */

orca_user_t* orca_user_init();
void orca_user_cleanup(orca_user_t *user);
void orca_get_user(orca_t *client, char user_id[], orca_user_t **p_user);
void orca_get_client(orca_t *client, orca_user_t **p_user);

#endif
