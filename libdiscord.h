#ifndef LIBDISCORD_H_
#define LIBDISCORD_H_

#include <stdint.h>
#include "discord-common.h"

/* This is the version number of the package from which this header
 *  file originates */
#define LIBDISCORD_VERSION "0.0.0-DEV"

/* The numeric version number is also available "in parts" by using
 *  these defines: */
#define LIBDISCORD_VERSION_MAJOR 0
#define LIBDISCORD_VERSION_MINOR 0
#define LIBDISCORD_VERSION_PATCH 0

/* Size limits encountered in the Docs and searching the web */
#define MAX_NAME_LEN           100 + 1
#define MAX_TOPIC_LEN          1024
#define MAX_DESCRIPTION_LEN    1024
#define MAX_USERNAME_LEN       32 + 1
#define MAX_DISCRIMINATOR_LEN  4 + 1
#define MAX_HASH_LEN           1024
#define MAX_LOCALE_LEN         16
#define MAX_EMAIL_LEN          254
#define MAX_REGION_LEN         16
#define MAX_HEADER_LEN         512
#define MAX_URL_LEN            512
#define MAX_REASON_LEN         512
#define MAX_MESSAGE_LEN        2000 + 1
#define MAX_PAYLOAD_LEN        4096

/* SNOWFLAKES
https://discord.com/developers/docs/reference#snowflakes */
#define SNOWFLAKE_INCREMENT           12
#define SNOWFLAKE_PROCESS_ID          17
#define SNOWFLAKE_INTERNAL_WORKER_ID  22
#define SNOWFLAKE_TIMESTAMP           64

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

namespace discord {

namespace channel {

/* CHANNEL OBJECT
 * https://discord.com/developers/docs/resources/channel#channel-object-channel-structure */
struct dati {
  char id[SNOWFLAKE_INTERNAL_WORKER_ID];
  int type;
  char guild_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  int position;
  //struct discord_overwrite_s **permission_overwrites;
  char name[MAX_NAME_LEN];
  char topic[MAX_TOPIC_LEN];
  bool nsfw;
  char last_message_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  int bitrate;
  int user_limit;
  int rate_limit_per_user;
  user::dati **recipients;
  char icon[MAX_HASH_LEN];
  char owner_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  char application_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  char parent_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  int64_t last_pin_timestamp;
  message::dati **messages;
};

dati* init();
void cleanup(dati *channel);

void pin_message(client *client, const char channel_id[], const char message_id[]);
void unpin_message(client *client, const char channel_id[], const char message_id[]);

namespace message {

/* DISCORD MESSAGE OBJECT
 * https://discord.com/developers/docs/resources/channel#message-object*/
struct dati {
  char id[SNOWFLAKE_INTERNAL_WORKER_ID];
  char channel_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  char guild_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  user::dati *author;
  //struct discord_guildmember_s *member;
  char content[MAX_MESSAGE_LEN];
  int64_t timestamp;
  int64_t edited_timestamp;
  bool tts;
  bool mention_everyone;
  user::dati **mentions;
  //struct discord_role_t **mention_roles;
  //struct discord_channelmention_s **mention_channels;
  //struct discord_attachment_s **attachments;
  //struct discord_embed_s **embeds;
  //strict discord_reaction_s **reactions;
  char nonce[SNOWFLAKE_INTERNAL_WORKER_ID];
  bool pinned;
  char webhook_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  int type;
  //struct discord_messageactivity_s *activity;
  //struct discord_messageapplication_s *application;
  //struct discord_messagereference_s *message_reference;
  int flags;
  //struct discord_sticker_s **stickers;
  dati *referenced_message;
};

dati* init();
void cleanup(dati *message);
void json_load(char *str, size_t len, void *p_message);

/* https://discord.com/developers/docs/resources/channel#create-message */
namespace create {

struct params {
  char *content;
  char *nonce;
  bool tts;
  char *file;
  //embed object
  char *payload_json;
  //allowed mentions
  struct message_reference {
    char message_id[SNOWFLAKE_INTERNAL_WORKER_ID];
    char channel_id[SNOWFLAKE_INTERNAL_WORKER_ID];
    char guild_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  };
};

void run(client *client, const char channel_id[], params *params, dati *p_message);

} // namespace create

void del(client *client, const char channel_id[], const char message_id[]);

} // namespace message

} // namespace channel

namespace guild {

/* GUILD OBJECT
 * https://discord.com/developers/docs/resources/guild#guild-object-guild-structure */
struct dati {
  char id[SNOWFLAKE_INTERNAL_WORKER_ID];
  char name[MAX_NAME_LEN];
  char icon[MAX_HASH_LEN];
  char splash[MAX_HASH_LEN];
  char discovery_splash[MAX_HASH_LEN];
  bool owner;
  char owner_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  int permissions;
  char permissions_new[SNOWFLAKE_INCREMENT];
  char region[MAX_REGION_LEN];
  char afk_channel_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  int afk_timeout;
  bool embed_enabled;
  char embed_channel_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  int verification_level;
  int default_message_notifications;
  int explicit_content_filter;
  //struct discord_role_t **roles;
  //struct discord_emoji_t **emojis;
  char **features;
  int mfa_level;
  char application_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  bool widget_enabled;
  char widget_channel_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  char system_channel_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  int system_channel_flags;
  char rules_channel_id[SNOWFLAKE_INTERNAL_WORKER_ID];
  int64_t joined_at;
  bool large;
  bool unavailable;
  int member_count;
  //struct discord_voicestate_s **voice_states;
  //struct discord_member_s **members;
  channel::dati **channels;
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
};

dati* init();
void cleanup(dati *guild);
void list_cleanup(dati **guild);
void json_load(char *str, size_t len, void *p_guild);
void json_list_load(char *str, size_t len, void *p_guilds);

void get(client *client, const char guild_id[], dati *p_guild);

namespace member {

/* GUILD MEMBER OBJECT
 * https://discord.com/developers/docs/resources/guild#guild-member-object*/
struct dati {
  user::dati *user;
  char nick[MAX_NAME_LEN];
  //roles
  int64_t joined_at;
  int64_t premium_since;
  bool deaf;
  bool mute;
  bool pending;
  //permissions
};

dati* init();
void cleanup(dati *member);
void list_cleanup(dati **members);
void json_load(char *str, size_t len, void *p_member);
void json_list_load(char *str, size_t len, void *p_members);

dati **get_list(client *client, const char guild_id[]);
void remove(client *client, const char guild_id[], const char user_id[]);

} // namespace member

namespace ban {

/* GUILD BAN OBJECT
 * https://discord.com/developers/docs/resources/guild#ban-object*/
struct dati {
  char reason[MAX_REASON_LEN + 1];
  user::dati *user;
};

dati* init();
void cleanup(dati *ban);
void list_cleanup(dati **bans);
void json_load(char *str, size_t len, void *p_ban);
void json_list_load(char *str, size_t len, void *p_ban);

void get(client *client, const char guild_id[], const char user_id[], dati *p_ban);
dati **get_list(client *client, const char guild_id[]);
void create(client *client, const char guild_id[], const char user_id[], int delete_message_days, const char reason[]);
void remove(client *client, const char guild_id[], const char user_id[], const char reason[]);

} // namespace ban

} // namespace guild

namespace user {

/* USER OBJECT
 * https://discord.com/developers/docs/resources/user#user-object-user-structure */
struct dati {
  char id[SNOWFLAKE_INTERNAL_WORKER_ID];
  char username[MAX_USERNAME_LEN];
  char discriminator[MAX_DISCRIMINATOR_LEN];
  char avatar[MAX_HASH_LEN];
  bool bot;
  bool sys;
  bool mfa_enabled;
  char locale[MAX_LOCALE_LEN];
  bool verified;
  char email[MAX_EMAIL_LEN];
  int flags;
  int premium_type;
  int public_flags;
  guild::dati **guilds;
};

dati* init();
void cleanup(dati *user);
void list_cleanup(dati **users);
void json_load(char *str, size_t len, void *p_user);
void json_list_load(char *str, size_t len, void *p_users);

void get(client *client, const char user_id[], dati *p_user);

namespace me {

void get(client *client, dati *p_user);
guild::dati** get_guilds(client *client);

} // namespace me

} // namespace user

/* discord-public.c */

void global_init();
void global_cleanup();

client* init(char token[]);
client* fast_init(const char config_file[]);
void cleanup(discord::client *client);

void setcb_idle(client *client, idle_cb *user_cb);
void setcb_ready(client *client, idle_cb *user_cb);
void setcb_message_create(client *client, message_cb *user_cb);
void setcb_message_update(client *client, message_cb *user_cb);
void setcb_message_delete(client *client, message_cb *user_cb);

void run(client *client);

void dump_json(client *client, char file[]);
void dump_curl(client *client, char file[]);
void* set_data(client *client, void *data);
void* get_data(client *client);

} // namespace discord

#endif
