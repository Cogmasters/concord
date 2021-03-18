#ifndef LIBDISCORD_H_
#define LIBDISCORD_H_

#include "json-actor-boxed.h"
#include "discord-common.h"

/* Size limits encountered in the Docs and searching the web */
#define MAX_NAME_LEN          100 + 1
#define MAX_TOPIC_LEN         1024 + 1
#define MAX_DESCRIPTION_LEN   2048 + 1
#define MAX_USERNAME_LEN      32 + 1
#define MAX_DISCRIMINATOR_LEN 4 + 1
#define MAX_SHA256_LEN        1024 + 1
#define MAX_LOCALE_LEN        16 + 1
#define MAX_EMAIL_LEN         254 + 1
#define MAX_REGION_LEN        16 + 1
#define MAX_REASON_LEN        512 + 1
#define MAX_MESSAGE_LEN       2000 + 1
#define MAX_PAYLOAD_LEN       4096 + 1

/* EMBED LIMITS
https://discord.com/developers/docs/resources/channel#embed-limits */
#define EMBED_TITLE_LEN       256 + 1
#define EMBED_DESCRIPTION_LEN 2048 + 1
#define EMBED_MAX_FIELDS      25
#define EMBED_FIELD_NAME_LEN  256 + 1
#define EMBED_FIELD_VALUE_LEN 1024 + 1
#define EMBED_FOOTER_TEXT_LEN 2048 + 1
#define EMBED_AUTHOR_NAME_LEN 256 + 1

/* WEBHOOK LIMITS
https://discord.com/developers/docs/resources/webhook#create-webhook */
#define WEBHOOK_NAME_LEN 80 + 1

/* SNOWFLAKES
https://discord.com/developers/docs/reference#snowflakes */
#define SNOWFLAKE_INCREMENT           12
#define SNOWFLAKE_PROCESS_ID          17
#define SNOWFLAKE_INTERNAL_WORKER_ID  22
#define SNOWFLAKE_TIMESTAMP           64

/* * * * * * * * * * * * * * * * * * * */
/* * * * STRUCTURES DECLARATIONS * * * */

namespace discord {

enum dispatch_code {
  UNKNOWN = 0,
  IDLE,
  READY,
  RESUMED,
  MESSAGE_CREATE,
  SB_MESSAGE_CREATE, //@todo this is temporary for wrapping JS
  MESSAGE_UPDATE,
  MESSAGE_DELETE,
  MESSAGE_DELETE_BULK,
  MESSAGE_REACTION_ADD,
  MESSAGE_REACTION_REMOVE,
  MESSAGE_REACTION_REMOVE_ALL,
  MESSAGE_REACTION_REMOVE_EMOJI,
  GUILD_MEMBER_ADD,
  GUILD_MEMBER_UPDATE,
  GUILD_MEMBER_REMOVE
};

/* START OF SHORTCUT ALIASES */

namespace presence = websockets::identify::status_update;
}

#include "./specs-code/all_enums.hh"
#include "./specs-code/all_structs.hh"

/* * * * * * * * * * * * * * * * * * */
/* * * * FUNCTION DECLARATIONS * * * */

namespace discord { /* discord-public.c */

void global_init();
void global_cleanup();

client* init(const char token[]);
client* config_init(const char config_file[]);
void cleanup(discord::client *client);

void add_intents(client *client, websockets::intents::code code);
void set_prefix(client *client, char *prefix);
void setcb_command(client *client, char *command, message_cb *user_cb);
void setcb(client *client, enum dispatch_code opt, ...);
void run(client *client);

void* set_data(client *client, void *data);
void* get_data(client *client);

void replace_presence(client *client, presence::dati *presence);
void set_presence(
  client *client, 
  presence::activity::dati *activity, 
  char status[], 
  bool afk);

namespace channel { /* discord-public-channel.c */

namespace get_channel {
void run(client *client, const u64_snowflake_t channel_id, dati *p_channel);
} // namespace get_channel

namespace delete_channel {
void run(client *client, const u64_snowflake_t channel_id, dati *p_channel);
} // namespace delete_channel

namespace add_pinned_channel_message {
void run(client *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id);
} // namespace add_pinned_channel_message

namespace delete_pinned_channel_message {
void run(client *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id);
} // namespace delete_pineed_channel_message

namespace get_channel_messages {
struct params {
  u64_snowflake_t around;
  u64_snowflake_t before;
  u64_snowflake_t after;
  int limit; // max number of messages (1-100)
};
void run(client *client, const u64_snowflake_t channel_id, params *params, NTL_T(message::dati) *p_messages);
} // namespace get_channel_messages

namespace delete_message {
void run(client *client, u64_snowflake_t channel_id, u64_snowflake_t message_id);
} // namespace delete_message

namespace create_message {
/* default is application/json unless any multipart/form-data parameter is set */
struct params {
  // common parameters
  char *content;
  char *nonce;
  bool tts;
  // parameters for application/json
  embed::dati *embed;
  allowed_mentions::dati *allowed_mentions;
  message::reference::dati *message_reference;
  // parameters for multipart/form-data
  struct { // FILE STRUCT @todo better explanation
    char *name; //if only name is set, will search in working directory
    char *content; //the file contents
    size_t size; //the size must accompany the content
  } file;
  char *payload_json;
};
void run(client *client, const u64_snowflake_t channel_id, params *params, message::dati *p_message);
} // namespace create_message

namespace edit_message {
struct params {
  char *content;
  embed::dati *embed; //must be initialized
  message::flags::code *flags;
  allowed_mentions::dati *allowed_mentions; //must be initialized
};
void run(client *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, params *params, message::dati *p_message);
} // namespace edit_message

namespace create_reaction {
void run(
  client *client, 
  const u64_snowflake_t channel_id, 
  const u64_snowflake_t message_id, 
  const u64_snowflake_t emoji_id, 
  const char emoji_name[]);
} // namespace create_reaction

namespace trigger_typing_indicator {
void run(client *client, const u64_snowflake_t channel_id);
} // namespace trigger_typing_indicator

namespace embed {
void change_thumbnail(dati *embed, char url[], char proxy_url[], int height, int width);
void change_image(dati *embed, char url[], char proxy_url[], int height, int width);
void change_video(dati *embed, char url[], char proxy_url[], int height, int width);
void change_footer(dati *embed, char text[], char icon_url[], char proxy_icon_url[]);
void change_provider(dati *embed, char name[], char url[]);
void change_author(dati *embed, char name[], char url[], char icon_url[], char proxy_icon_url[]);
void add_field(dati *embed, char name[], char value[], bool Inline);
} // namespace embed

namespace overwrite {
void append(
  NTL_T(dati) *permission_overwrites, 
  u64_snowflake_t id, 
  int type, 
  permissions::bitwise_flags allow, permissions::bitwise_flags deny);
} // namespace overwrite

} // namespace channel

namespace emoji { /* discord-public-emoji.cpp */

namespace list_guild_emojis {
void run(client *client, const u64_snowflake_t guild_id, NTL_T(dati) *p_emojis);
} // namespace list_guild_emojis

} // namespace emoji

namespace guild { /* discord-public-guild.cpp */

namespace get_guild {
void run(client *client, const u64_snowflake_t guild_id, dati *p_guild);
} // namespace get_guild

namespace get_channels {
void run(client *client, const u64_snowflake_t guild_id, NTL_T(channel::dati) *p_channels);
} // namespace get_channels

namespace create_channel {
void run(client *client, const u64_snowflake_t guild_id, params *params, channel::dati *p_channel);
} // namespace create_channel

namespace get_guild_member {
void  run(client *client, u64_snowflake_t guild_id, u64_snowflake_t user_id, member::dati **p_member);
} // get_guild_member

namespace list_guild_members {
struct params {
  int limit; // the number of members to return (1-1000)
  u64_snowflake_t after; // the highest user id in the previous page
};
void run(client *client, const u64_snowflake_t guild_id, struct params *params, NTL_T(member::dati) *p_members);
} // namespace list_guild_members

namespace modify_guild_member {
void run(client *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, params *params, member::dati *p_member);
} // namespace modify_guild_member

namespace remove_guild_member {
void run(client *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id);
} // namespace remove_guild_member

namespace get_guild_bans {
void run(client *client, const u64_snowflake_t guild_id, NTL_T(ban::dati) *p_bans);
} // namespace get_guild_bans

namespace get_guild_ban {
void run(client *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, ban::dati *p_ban);
} // namespace get_guild_ban

namespace create_guild_ban {
void run(client *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, int delete_message_days, const char reason[]);
} // namespace create_guild_ban

namespace remove_guild_ban {
void run(client *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, const char reason[]);
} // namespace remove_guild_ban

namespace get_guild_roles {
void run(client *client, const u64_snowflake_t guild_id, NTL_T(role::dati) *p_roles);
} // namespace get_guild_roles

namespace create_guild_role {
void run(client *client, const u64_snowflake_t guild_id, params *params, role::dati *p_role);
} // namespace create_guild_role

namespace delete_guild_role {
void run(client *client, const u64_snowflake_t guild_id, const u64_snowflake_t role_id);
} // namespace delete_guild_role

} // namespace guild

namespace user { /* discord-public-user.cpp */

namespace get_user {
void run(client *client, const u64_snowflake_t user_id, dati *p_user);
} // namespace get_user

namespace get_current_user {
void run(client *client, dati *p_user);
void sb_run(client *client, struct sized_buffer *p_sb_user);
} // namespace get_current_user

namespace get_current_user_guilds {
void run(client *client, NTL_T(guild::dati) *p_guilds);
} // namespace get_current_user_guilds

namespace leave_guild {
void run(client *client, const u64_snowflake_t guild_id);
} // namespace leave_guild

} // namespace user

} // namespace discord

#include "user-defined.h"
#include "./specs-code/all_fun.hh"
#endif
