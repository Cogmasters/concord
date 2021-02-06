#ifndef LIBDISCORD_H_
#define LIBDISCORD_H_

#include <inttypes.h>
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
#define MAX_TOPIC_LEN          1024 + 1
#define MAX_DESCRIPTION_LEN    2048 + 1
#define MAX_USERNAME_LEN       32 + 1
#define MAX_DISCRIMINATOR_LEN  4 + 1
#define MAX_HASH_LEN           1024 + 1
#define MAX_LOCALE_LEN         16 + 1
#define MAX_EMAIL_LEN          254 + 1
#define MAX_REGION_LEN         16 + 1
#define MAX_HEADER_LEN         512 + 1
#define MAX_REASON_LEN         512 + 1
#define MAX_MESSAGE_LEN        2000 + 1
#define MAX_PAYLOAD_LEN        4096 + 1


/* ENDPOINTS */
#define MESSAGES              "/messages"
#define MESSAGE               MESSAGES"/%" PRIu64

#define CHANNELS              "/channels"
#define CHANNEL               CHANNELS"/%" PRIu64

#define REACTION_EMOJI        CHANNEL MESSAGE"/reactions/%" PRIu64
#define REACTION_EMOJI_USER   REACTION_EMOJI"/%" PRIu64

#define PINNED_MESSAGES       CHANNEL"/pins"
#define PINNED_MESSAGE        PINNED_MESSAGES"/%" PRIu64

#define GUILDS                "/guilds"
#define GUILD                 GUILDS"/%" PRIu64

#define USERS                 "/users"
#define USER                  USERS"/%" PRIu64
#define ME                    USERS"/@me"

#define MEMBERS               "/members"
#define MEMBER                MEMBERS"/%" PRIu64

#define BANS                  "/bans"
#define BAN                   BANS"/%" PRIu64

#define GATEWAY               "/gateway"
#define BOT                   "/bot"


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
  GUILD_STORE     = 6
};

namespace discord {

namespace channel {

/* CHANNEL OBJECT
 * https://discord.com/developers/docs/resources/channel#channel-object-channel-structure */
struct dati {
  uint64_t id;
  int type;
  uint64_t guild_id;
  int position;
  //struct discord_overwrite_s **permission_overwrites;
  char name[MAX_NAME_LEN];
  char topic[MAX_TOPIC_LEN];
  bool nsfw;
  uint64_t last_message_id;
  int bitrate;
  int user_limit;
  int rate_limit_per_user;
  user::dati **recipients;
  char icon[MAX_HASH_LEN];
  uint64_t owner_id;
  uint64_t application_id;
  uint64_t parent_id;
  int64_t last_pin_timestamp;
  message::dati **messages;
};

dati* init();
void cleanup(dati *channel);

void pin_message(client *client, const uint64_t channel_id, const uint64_t message_id);
void unpin_message(client *client, const uint64_t channel_id, const uint64_t message_id);

namespace message {

/* DISCORD MESSAGE OBJECT
 * https://discord.com/developers/docs/resources/channel#message-object*/
struct dati {
  uint64_t id;
  uint64_t channel_id;
  uint64_t guild_id;
  user::dati *author;
  guild::member::dati *member;
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
  char *nonce;
  bool pinned;
  uint64_t webhook_id;
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
    uint64_t message_id;
    uint64_t channel_id;
    uint64_t guild_id;
  };
};

void run(client *client, const uint64_t channel_id, params *params, dati *p_message);

} // namespace create

void del(client *client, const uint64_t channel_id, const uint64_t message_id);

} // namespace message

} // namespace channel

namespace guild {

/* GUILD OBJECT
 * https://discord.com/developers/docs/resources/guild#guild-object-guild-structure */
struct dati {
  uint64_t id;
  char name[MAX_NAME_LEN];
  char icon[MAX_HASH_LEN];
  char splash[MAX_HASH_LEN];
  char discovery_splash[MAX_HASH_LEN];
  bool owner;
  uint64_t owner_id;
  int permissions;
  char region[MAX_REGION_LEN];
  uint64_t afk_channel_id;
  int afk_timeout;
  bool embed_enabled;
  uint64_t embed_channel_id;
  int verification_level;
  int default_message_notifications;
  int explicit_content_filter;
  //struct discord_role_t **roles;
  //struct discord_emoji_t **emojis;
  char **features;
  int mfa_level;
  uint64_t application_id;
  bool widget_enabled;
  uint64_t widget_channel_id;
  uint64_t system_channel_id;
  int system_channel_flags;
  uint64_t rules_channel_id;
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
  char vanity_url_code[MAX_URL_LEN];
  char description[MAX_DESCRIPTION_LEN];
  char banner[MAX_HASH_LEN];
  int premium_tier;
  int premium_subscription_count;
  char preferred_locale[MAX_LOCALE_LEN];
  uint64_t public_updates_channel_id;
  int max_video_channel_users;
  int approximate_member_count;
  int approximate_presence_count;
};

dati* init();
void cleanup(dati *guild);
void list_cleanup(dati **guild);
void json_load(char *str, size_t len, void *p_guild);
void json_list_load(char *str, size_t len, void *p_guilds);

void get(client *client, const uint64_t guild_id, dati *p_guild);

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

dati **get_list(client *client, const uint64_t guild_id);
void remove(client *client, const uint64_t guild_id, const uint64_t user_id);

} // namespace member

namespace ban {

/* GUILD BAN OBJECT
 * https://discord.com/developers/docs/resources/guild#ban-object*/
struct dati {
  char reason[MAX_REASON_LEN];
  user::dati *user;
};

dati* init();
void cleanup(dati *ban);
void list_cleanup(dati **bans);
void json_load(char *str, size_t len, void *p_ban);
void json_list_load(char *str, size_t len, void *p_ban);

void get(client *client, const uint64_t guild_id, const uint64_t user_id, dati *p_ban);
dati **get_list(client *client, const uint64_t guild_id);
void create(client *client, const uint64_t guild_id, const uint64_t user_id, int delete_message_days, const char reason[]);
void remove(client *client, const uint64_t guild_id, const uint64_t user_id, const char reason[]);

} // namespace ban

} // namespace guild

namespace user {

/* USER OBJECT
 * https://discord.com/developers/docs/resources/user#user-object-user-structure */
struct dati {
  uint64_t id;
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

void get(client *client, const uint64_t user_id, dati *p_user);

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
void setcb_message_delete(client *client, message_delete_cb *user_cb);
void setcb_message_delete_bulk(client *client, message_delete_bulk_cb *user_cb);
void setcb_guild_member_add(client *client, guild_member_cb *user_cb);
void setcb_guild_member_update(client *client, guild_member_cb *user_cb);
void setcb_guild_member_remove(client *client, guild_member_remove_cb *user_cb);

void run(client *client);

void dump_json(client *client, char file[]);
void dump_curl(client *client, char file[]);
void* set_data(client *client, void *data);
void* get_data(client *client);

} // namespace discord

#endif
