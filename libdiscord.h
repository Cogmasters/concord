#ifndef LIBDISCORD_H_
#define LIBDISCORD_H_

#include "json-actor-boxed.h"
#include "discord-common.h"


struct discord_channel_get_channel_messages_params {
  u64_snowflake_t around;
  u64_snowflake_t before;
  u64_snowflake_t after;
  int limit; // max number of messages (1-100)
};

/* default is application/json unless any multipart/form-data parameter is set */
struct discord_channel_create_message_params {
  // common parameters
  char *content;
  char *nonce;
  bool tts;
  // parameters for application/json
  struct discord_channel_embed_dati *embed;
  struct discord_channel_allowed_mentions_dati *allowed_mentions;
  struct discord_channel_message_reference_dati *message_reference;
  // parameters for multipart/form-data
  struct { // FILE STRUCT @todo better explanation
    char *name; //if only name is set, will search in working directory
    char *content; //the file contents
    size_t size; //the size must accompany the content
  } file;
  char *payload_json;
};

struct discord_channel_edit_message_params {
  char *content;
  struct discord_channel_embed_dati *embed; //must be initialized
  enum discord_channel_message_flags_code *flags;
  struct discord_channel_allowed_mentions_dati *allowed_mentions; //must be initialized
};

struct discord_guild_list_guild_members_params {
  int limit; // the number of members to return (1-1000)
  u64_snowflake_t after; // the highest user id in the previous page
};

// @todo add discord_ prefix
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

void discord_replace_presence(struct discord_client *client, struct discord_presence_dati *presence);
void discord_set_presence(struct discord_client *client, struct discord_presence_activity_dati *activity, char status[], bool afk);


// EMBED MISC FUNCTIONS
void discord_embed_set_thumbnail(struct discord_channel_embed_dati *embed, char url[], char proxy_url[], int height, int width);
void discord_embed_set_image(struct discord_channel_embed_dati *embed, char url[], char proxy_url[], int height, int width);
void discord_embed_set_video(struct discord_channel_embed_dati *embed, char url[], char proxy_url[], int height, int width);
void discord_embed_set_footer(struct discord_channel_embed_dati *embed, char text[], char icon_url[], char proxy_icon_url[]);
void discord_embed_set_provider(struct discord_channel_embed_dati *embed, char name[], char url[]);
void discord_embed_set_author(struct discord_channel_embed_dati *embed, char name[], char url[], char icon_url[], char proxy_icon_url[]);
void discord_embed_add_field(struct discord_channel_embed_dati *embed, char name[], char value[], bool Inline);

// CHANNEL OVERWRITE MISC FUNCTIONS
void discord_overwrite_append(
  NTL_T(struct discord_channel_overwrite_dati) *permission_overwrites, 
  u64_snowflake_t id, 
  int type, 
  enum discord_permissions_bitwise_flags allow, 
  enum discord_permissions_bitwise_flags deny);


// CHANNEL PUBLIC FUNCTIONS
void discord_get_channel(struct discord_client *client, const u64_snowflake_t channel_id, struct discord_channel_dati *p_channel);
void discord_delete_channel(struct discord_client *client, const u64_snowflake_t channel_id, struct discord_channel_dati *p_channel);
void discord_add_pinned_channel_message(struct discord_client *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id);
void discord_delete_pinned_channel_message(struct discord_client *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id);
void discord_get_channel_messages(struct discord_client *client, const u64_snowflake_t channel_id, struct discord_channel_get_channel_messages_params *params, NTL_T(struct discord_channel_message_dati) *p_messages);
void discord_delete_message(struct discord_client *client, u64_snowflake_t channel_id, u64_snowflake_t message_id);
void discord_create_message(struct discord_client *client, const u64_snowflake_t channel_id, struct discord_channel_create_message_params *params, struct discord_channel_message_dati *p_message);
void discord_edit_message(struct discord_client *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, struct discord_channel_edit_message_params *params, struct discord_channel_message_dati *p_message);
void discord_create_reaction(struct discord_client *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, const u64_snowflake_t emoji_id, const char emoji_name[]);
void discord_trigger_typing_indicator(struct discord_client *client, const u64_snowflake_t channel_id);

// EMOJI PUBLIC FUNCTIONS
void discord_list_guild_emojis(struct discord_client *client, const u64_snowflake_t guild_id, NTL_T(struct discord_emoji_dati) *p_emojis);

// GUILD PUBLIC FUNCTIONS
void discord_get_guild(struct discord_client *client, const u64_snowflake_t guild_id, struct discord_guild_dati *p_guild);
void discord_get_channels(struct discord_client *client, const u64_snowflake_t guild_id, NTL_T(struct discord_channel_dati) *p_channels);
void discord_create_channel(struct discord_client *client, const u64_snowflake_t guild_id, struct discord_guild_create_channel_params *params, struct discord_channel_dati *p_channel);
void  discord_get_guild_member(struct discord_client *client, u64_snowflake_t guild_id, u64_snowflake_t user_id, struct discord_guild_member_dati *p_member);
void discord_list_guild_members(struct discord_client *client, const u64_snowflake_t guild_id, struct struct discord_guild_list_guild_members_params *params, NTL_T(struct discord_guild_member_dati) *p_members);
void discord_modify_guild_member(struct discord_client *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, struct discord_guild_modify_guild_member_params *params, struct discord_guild_member_dati *p_member);
void discord_remove_guild_member(struct discord_client *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id);
void discord_get_guild_bans(struct discord_client *client, const u64_snowflake_t guild_id, NTL_T(struct discord_guild_ban_dati) *p_bans);
void discord_get_guild_ban(struct discord_client *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, struct discord_guild_ban_dati *p_ban);
void discord_create_guild_ban(struct discord_client *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, int delete_message_days, const char reason[]);
void discord_remove_guild_ban(struct discord_client *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, const char reason[]);
void discord_get_guild_roles(struct discord_client *client, const u64_snowflake_t guild_id, NTL_T(struct discord_guild_role_dati) *p_roles);
void discord_create_guild_role(struct discord_client *client, const u64_snowflake_t guild_id, struct discord_guild_create_guild_role_params *params, struct discord_guild_role_dati *p_role);
void discord_delete_guild_role(struct discord_client *client, const u64_snowflake_t guild_id, const u64_snowflake_t role_id);

// USER PUBLIC FUNCTIONS
void discord_get_user(struct discord_client *client, const u64_snowflake_t user_id, struct discord_user_dati *p_user);
void discord_get_current_user(struct discord_client *client, struct discord_user_dati *p_user);
void sb_discord_get_current_user(struct discord_client *client, struct sized_buffer *p_sb_user);
void discord_get_current_user_guilds(struct discord_client *client, NTL_T(struct discord_guild_dati) *p_guilds);
void discord_leave_guild(struct discord_client *client, const u64_snowflake_t guild_id);

// GATEWAY PUBLIC FUNCTIONS
void discord_get_gateway(struct discord_client *client, struct discord_session *p_session);
void discord_get_gateway_bot(struct discord_client *client, struct discord_session *p_session);

#include "user-defined.h"
#include "./specs-code/all_fun.h"
#endif
