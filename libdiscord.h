#ifndef LIBDISCORD_H_
#define LIBDISCORD_H_

#include "json-actor-boxed.h"
#include "discord-common.h"


namespace discord {

namespace presence = discord::gateway::identify::status_update;

namespace channel { /* discord-public-channel.c */
namespace get_channel_messages {
struct params {
  u64_snowflake_t around;
  u64_snowflake_t before;
  u64_snowflake_t after;
  int limit; // max number of messages (1-100)
};
} // namespace get_channel_messages
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
} // namespace create_message

namespace edit_message {
struct params {
  char *content;
  discord::channel::embed::dati *embed; //must be initialized
  discord::channel::message::flags::code *flags;
  discord::channel::allowed_mentions::dati *allowed_mentions; //must be initialized
};
} // namespace edit_message
} // namespace channel

namespace guild { /* discord-public-guild.cpp */
namespace list_guild_members {
struct params {
  int limit; // the number of members to return (1-1000)
  u64_snowflake_t after; // the highest user id in the previous page
};
} // namespace list_guild_members
} // namespace guild

} // namespace discord

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

/* * * * * * * * * * * * * * * * * * */
/* * * * FUNCTION DECLARATIONS * * * */

void discord_global_init();
void discord_global_cleanup();

struct discord_client* discord_init(const char token[]);
struct discord_client* discord_config_init(const char config_file[]);
void discord_cleanup(struct discord_client *client);

void discord_add_intents(struct discord_client *client, int intent_code);
void discord_set_prefix(struct discord_client *client, char *prefix);
void discord_setcb_command(struct discord_client *client, char *command, message_cb *user_cb);
void discord_setcb(struct discord_client *client, enum dispatch_code opt, ...);
void discord_run(struct discord_client *client);

void* discord_set_data(struct discord_client *client, void *data);
void* discord_get_data(struct discord_client *client);

void discord_replace_presence(struct discord_client *client, discord::presence::dati *presence);
void discord_set_presence(struct discord_client *client, discord::presence::activity::dati *activity, char status[], bool afk);


// EMBED MISC FUNCTIONS
void discord_embed_set_thumbnail(discord::channel::embed::dati *embed, char url[], char proxy_url[], int height, int width);
void discord_embed_set_image(discord::channel::embed::dati *embed, char url[], char proxy_url[], int height, int width);
void discord_embed_set_video(discord::channel::embed::dati *embed, char url[], char proxy_url[], int height, int width);
void discord_embed_set_footer(discord::channel::embed::dati *embed, char text[], char icon_url[], char proxy_icon_url[]);
void discord_embed_set_provider(discord::channel::embed::dati *embed, char name[], char url[]);
void discord_embed_set_author(discord::channel::embed::dati *embed, char name[], char url[], char icon_url[], char proxy_icon_url[]);
void discord_embed_add_field(discord::channel::embed::dati *embed, char name[], char value[], bool Inline);

// CHANNEL OVERWRITE MISC FUNCTIONS
void discord_overwrite_append(
  NTL_T(discord::channel::overwrite::dati) *permission_overwrites, 
  u64_snowflake_t id, 
  int type, 
  discord::permissions::bitwise_flags allow, discord::permissions::bitwise_flags deny);


// CHANNEL PUBLIC FUNCTIONS
void discord_get_channel(struct discord_client *client, const u64_snowflake_t channel_id, discord::channel::dati *p_channel);
void discord_delete_channel(struct discord_client *client, const u64_snowflake_t channel_id, discord::channel::dati *p_channel);
void discord_add_pinned_channel_message(struct discord_client *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id);
void discord_delete_pinned_channel_message(struct discord_client *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id);
void discord_get_channel_messages(struct discord_client *client, const u64_snowflake_t channel_id, discord::channel::get_channel_messages::params *params, NTL_T(discord::channel::message::dati) *p_messages);
void discord_delete_message(struct discord_client *client, u64_snowflake_t channel_id, u64_snowflake_t message_id);
void discord_create_message(struct discord_client *client, const u64_snowflake_t channel_id, discord::channel::create_message::params *params, discord::channel::message::dati *p_message);
void discord_edit_message(struct discord_client *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, discord::channel::edit_message::params *params, discord::channel::message::dati *p_message);
void discord_create_reaction(struct discord_client *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, const u64_snowflake_t emoji_id, const char emoji_name[]);
void discord_trigger_typing_indicator(struct discord_client *client, const u64_snowflake_t channel_id);

// EMOJI PUBLIC FUNCTIONS
void discord_list_guild_emojis(struct discord_client *client, const u64_snowflake_t guild_id, NTL_T(discord::emoji::dati) *p_emojis);

// GUILD PUBLIC FUNCTIONS
void discord_get_guild(struct discord_client *client, const u64_snowflake_t guild_id, discord::guild::dati *p_guild);
void discord_get_channels(struct discord_client *client, const u64_snowflake_t guild_id, NTL_T(discord::channel::dati) *p_channels);
void discord_create_channel(struct discord_client *client, const u64_snowflake_t guild_id, discord::guild::create_channel::params *params, discord::channel::dati *p_channel);
void  discord_get_guild_member(struct discord_client *client, u64_snowflake_t guild_id, u64_snowflake_t user_id, discord::guild::member::dati *p_member);
void discord_list_guild_members(struct discord_client *client, const u64_snowflake_t guild_id, struct discord::guild::list_guild_members::params *params, NTL_T(discord::guild::member::dati) *p_members);
void discord_modify_guild_member(struct discord_client *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, discord::guild::modify_guild_member::params *params, discord::guild::member::dati *p_member);
void discord_remove_guild_member(struct discord_client *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id);
void discord_get_guild_bans(struct discord_client *client, const u64_snowflake_t guild_id, NTL_T(discord::guild::ban::dati) *p_bans);
void discord_get_guild_ban(struct discord_client *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, discord::guild::ban::dati *p_ban);
void discord_create_guild_ban(struct discord_client *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, int delete_message_days, const char reason[]);
void discord_remove_guild_ban(struct discord_client *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, const char reason[]);
void discord_get_guild_roles(struct discord_client *client, const u64_snowflake_t guild_id, NTL_T(discord::guild::role::dati) *p_roles);
void discord_create_guild_role(struct discord_client *client, const u64_snowflake_t guild_id, discord::guild::create_guild_role::params *params, discord::guild::role::dati *p_role);
void discord_delete_guild_role(struct discord_client *client, const u64_snowflake_t guild_id, const u64_snowflake_t role_id);

// USER PUBLIC FUNCTIONS
void discord_get_user(struct discord_client *client, const u64_snowflake_t user_id, discord::user::dati *p_user);
void discord_get_current_user(struct discord_client *client, discord::user::dati *p_user);
void sb_discord_get_current_user(struct discord_client *client, struct sized_buffer *p_sb_user);
void discord_get_current_user_guilds(struct discord_client *client, NTL_T(discord::guild::dati) *p_guilds);
void discord_leave_guild(struct discord_client *client, const u64_snowflake_t guild_id);

// GATEWAY PUBLIC FUNCTIONS
void discord_get_gateway(struct discord_client *client, struct discord_session *p_session);
void discord_get_gateway_bot(struct discord_client *client, struct discord_session *p_session);

#include "user-defined.h"
#include "./specs-code/all_fun.h"
#endif
