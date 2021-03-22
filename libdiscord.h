#ifndef LIBDISCORD_H_
#define LIBDISCORD_H_

#include "json-actor-boxed.h"
#include "discord-common.h"

namespace discord {

namespace presence = discord::gateway::identify::status_update;

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
}

/* * * * * * * * * * * * * * * * * * */
/* * * * FUNCTION DECLARATIONS * * * */

namespace discord { /* discord-public.c */

void global_init();
void global_cleanup();

discord::client* init(const char token[]);
discord::client* config_init(const char config_file[]);
void cleanup(discord::client *client);

void add_intents(discord::client *client, int intent_code);
void set_prefix(discord::client *client, char *prefix);
void setcb_command(discord::client *client, char *command, message_cb *user_cb);
void setcb(discord::client *client, enum dispatch_code opt, ...);
void run(discord::client *client);

void* set_data(discord::client *client, void *data);
void* get_data(discord::client *client);

void replace_presence(discord::client *client, discord::presence::dati *presence);
void set_presence(
  discord::client *client, 
  discord::presence::activity::dati *activity, 
  char status[], 
  bool afk);

namespace channel { /* discord-public-channel.c */

namespace get_channel {
void run(discord::client *client, const u64_snowflake_t channel_id, discord::channel::dati *p_channel);
} // namespace get_channel

namespace delete_channel {
void run(discord::client *client, const u64_snowflake_t channel_id, discord::channel::dati *p_channel);
} // namespace delete_channel

namespace add_pinned_channel_message {
void run(discord::client *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id);
} // namespace add_pinned_channel_message

namespace delete_pinned_channel_message {
void run(discord::client *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id);
} // namespace delete_pineed_channel_message

namespace get_channel_messages {
struct params {
  u64_snowflake_t around;
  u64_snowflake_t before;
  u64_snowflake_t after;
  int limit; // max number of messages (1-100)
};
void run(discord::client *client, const u64_snowflake_t channel_id, discord::channel::get_channel_messages::params *params, NTL_T(discord::channel::message::dati) *p_messages);
} // namespace get_channel_messages

namespace delete_message {
void run(discord::client *client, u64_snowflake_t channel_id, u64_snowflake_t message_id);
} // namespace delete_message

namespace create_message {
/* default is application/json unless any multipart/form-data parameter is set */
struct params {
  // common parameters
  char *content;
  char *nonce;
  bool tts;
  // parameters for application/json
  discord::channel::embed::dati *embed;
  discord::channel::allowed_mentions::dati *allowed_mentions;
  discord::channel::message::reference::dati *message_reference;
  // parameters for multipart/form-data
  struct { // FILE STRUCT @todo better explanation
    char *name; //if only name is set, will search in working directory
    char *content; //the file contents
    size_t size; //the size must accompany the content
  } file;
  char *payload_json;
};
void run(discord::client *client, const u64_snowflake_t channel_id, discord::channel::create_message::params *params, discord::channel::message::dati *p_message);
} // namespace create_message

namespace edit_message {
struct params {
  char *content;
  discord::channel::embed::dati *embed; //must be initialized
  discord::channel::message::flags::code *flags;
  discord::channel::allowed_mentions::dati *allowed_mentions; //must be initialized
};
void run(discord::client *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, discord::channel::edit_message::params *params, discord::channel::message::dati *p_message);
} // namespace edit_message

namespace create_reaction {
void run(
  discord::client *client, 
  const u64_snowflake_t channel_id, 
  const u64_snowflake_t message_id, 
  const u64_snowflake_t emoji_id, 
  const char emoji_name[]);
} // namespace create_reaction

namespace trigger_typing_indicator {
void run(discord::client *client, const u64_snowflake_t channel_id);
} // namespace trigger_typing_indicator

namespace embed {
void change_thumbnail(discord::channel::embed::dati *embed, char url[], char proxy_url[], int height, int width);
void change_image(discord::channel::embed::dati *embed, char url[], char proxy_url[], int height, int width);
void change_video(discord::channel::embed::dati *embed, char url[], char proxy_url[], int height, int width);
void change_footer(discord::channel::embed::dati *embed, char text[], char icon_url[], char proxy_icon_url[]);
void change_provider(discord::channel::embed::dati *embed, char name[], char url[]);
void change_author(discord::channel::embed::dati *embed, char name[], char url[], char icon_url[], char proxy_icon_url[]);
void add_field(discord::channel::embed::dati *embed, char name[], char value[], bool Inline);
} // namespace embed

namespace overwrite {
void append(
  NTL_T(discord::channel::overwrite::dati) *permission_overwrites, 
  u64_snowflake_t id, 
  int type, 
  discord::permissions::bitwise_flags allow, discord::permissions::bitwise_flags deny);
} // namespace overwrite

} // namespace channel

namespace emoji { /* discord-public-emoji.cpp */

namespace list_guild_emojis {
void run(discord::client *client, const u64_snowflake_t guild_id, NTL_T(discord::emoji::dati) *p_emojis);
} // namespace list_guild_emojis

} // namespace emoji

namespace guild { /* discord-public-guild.cpp */

namespace get_guild {
void run(discord::client *client, const u64_snowflake_t guild_id, discord::guild::dati *p_guild);
} // namespace get_guild

namespace get_channels {
void run(discord::client *client, const u64_snowflake_t guild_id, NTL_T(discord::channel::dati) *p_channels);
} // namespace get_channels

namespace create_channel {
void run(discord::client *client, const u64_snowflake_t guild_id, discord::guild::create_channel::params *params, discord::channel::dati *p_channel);
} // namespace create_channel

namespace get_guild_member {
void  run(discord::client *client, u64_snowflake_t guild_id, u64_snowflake_t user_id, discord::guild::member::dati *p_member);
} // get_guild_member

namespace list_guild_members {
struct params {
  int limit; // the number of members to return (1-1000)
  u64_snowflake_t after; // the highest user id in the previous page
};
void run(discord::client *client, const u64_snowflake_t guild_id, struct discord::guild::list_guild_members::params *params, NTL_T(discord::guild::member::dati) *p_members);
} // namespace list_guild_members

namespace modify_guild_member {
void run(discord::client *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, discord::guild::modify_guild_member::params *params, discord::guild::member::dati *p_member);
} // namespace modify_guild_member

namespace remove_guild_member {
void run(discord::client *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id);
} // namespace remove_guild_member

namespace get_guild_bans {
void run(discord::client *client, const u64_snowflake_t guild_id, NTL_T(discord::guild::ban::dati) *p_bans);
} // namespace get_guild_bans

namespace get_guild_ban {
void run(discord::client *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, discord::guild::ban::dati *p_ban);
} // namespace get_guild_ban

namespace create_guild_ban {
void run(discord::client *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, int delete_message_days, const char reason[]);
} // namespace create_guild_ban

namespace remove_guild_ban {
void run(discord::client *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, const char reason[]);
} // namespace remove_guild_ban

namespace get_guild_roles {
void run(discord::client *client, const u64_snowflake_t guild_id, NTL_T(discord::guild::role::dati) *p_roles);
} // namespace get_guild_roles

namespace create_guild_role {
void run(discord::client *client, const u64_snowflake_t guild_id, discord::guild::create_guild_role::params *params, discord::guild::role::dati *p_role);
} // namespace create_guild_role

namespace delete_guild_role {
void run(discord::client *client, const u64_snowflake_t guild_id, const u64_snowflake_t role_id);
} // namespace delete_guild_role

} // namespace guild

namespace user { /* discord-public-user.cpp */

namespace get_user {
void run(discord::client *client, const u64_snowflake_t user_id, discord::user::dati *p_user);
} // namespace get_user

namespace get_current_user {
void run(discord::client *client, discord::user::dati *p_user);
void sb_run(discord::client *client, struct sized_buffer *p_sb_user);
} // namespace get_current_user

namespace get_current_user_guilds {
void run(discord::client *client, NTL_T(discord::guild::dati) *p_guilds);
} // namespace get_current_user_guilds

namespace leave_guild {
void run(discord::client *client, const u64_snowflake_t guild_id);
} // namespace leave_guild

} // namespace user

namespace gateway {

namespace get_gateway {
void run(discord::client *client, discord::gateway::session::dati *p_session);
} // namespace get_gateway

namespace get_gateway_bot {
void run(discord::client *client, discord::gateway::session::dati *p_session);
} // namespace get_gateway_bot

} // namespace gateway

} // namespace discord

#include "user-defined.h"
#include "./specs-code/all_fun.hh"
#endif
