#ifndef DISCORD_H
#define DISCORD_H

#include <stdbool.h>

#include "json-actor-boxed.h"

typedef uint64_t u64_unix_ms_t;
typedef uint64_t u64_snowflake_t;

struct discord; //forward declaration

struct discord_voice { /* VOICE CONNECTION STRUCTURE */
  char token[128];            // the session token
  char session_id[512];       // the session id
  u64_snowflake_t server_id;  // the session guild id
  u64_snowflake_t channel_id; // the session channel id
  u64_snowflake_t user_id;    // the bot user id
  
  // obtained after on_ready_cb()
  int ssrc;    // secret
  char server_ip[64]; // server external IP
  int server_port; // server external port
  // obtained after succesful rtp_ip_discovery()
  char client_ip[64]; // client external IP
  int client_port;  // client external port

  struct _discord_voice *priv; // declared at discord-common.h
};

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
#define MAX_URL_LEN           512 + 1

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

#include "./specs-code/all_opaque_struct.h"
#include "./specs-code/all_enums.h"
#include "./specs-code/all_structs.h"


/* IDLE CALLBACK (runs on every iteration, no trigger required) */
typedef void (idle_cb)(struct discord *client, const struct discord_user *bot);

typedef void (event_raw_cb)(
    struct discord *client, 
    enum discord_gateway_events event, 
    struct sized_buffer *sb_bot, 
    struct sized_buffer *event_data);

/* GUILD ROLE EVENTS CALLBACKS */
typedef void (guild_role_cb)(
    struct discord *client, const struct discord_user *bot,
    const u64_snowflake_t guild_id,
    const struct discord_guild_role *role);
typedef void (guild_role_delete_cb)(
    struct discord *client, const struct discord_user *bot,
    const u64_snowflake_t guild_id,
    const u64_snowflake_t role_id);

/* GUILD MEMBER EVENTS CALLBACKS */
typedef void (guild_member_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t guild_id, 
    const struct discord_guild_member *member);
typedef void (guild_member_remove_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t guild_id, 
    const struct discord_user *user);

/* GUILD BAN EVENTS CALLBACKS */
typedef void (guild_ban_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t guild_id, 
    const struct discord_user *user);

/* MESSAGE EVENTS CALLBACKS */
typedef void (message_cb)(
    struct discord *client, const struct discord_user *bot, 
    const struct discord_message *message);
typedef void (sb_message_cb)(
    struct discord *client, const struct discord_user *bot,
    struct sized_buffer *sb_bot,
    const struct discord_message *message,
    struct sized_buffer *msg_payload);
typedef void (message_delete_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t id, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t guild_id);
typedef void (message_delete_bulk_cb)(
    struct discord *client, const struct discord_user *bot, 
    const NTL_T(ja_u64) ids, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t guild_id);

/* CHANNEL EVENTS CALLBACKS */
typedef void (channel_cb)(
    struct discord *client, const struct discord_user *bot, 
    const struct discord_channel *channel);
typedef void (channel_pins_update_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t guild_id,
    const u64_snowflake_t channel_id,
    const u64_unix_ms_t last_pin_timestamp);

/* MESSAGE REACTION EVENTS CALLBACKS */
typedef void (message_reaction_add_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t user_id,
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t message_id, 
    const u64_snowflake_t guild_id, 
    const struct discord_guild_member *member, 
    const struct discord_emoji *emoji);
typedef void (message_reaction_remove_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t user_id,
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t message_id, 
    const u64_snowflake_t guild_id, 
    const struct discord_emoji *emoji);
typedef void (message_reaction_remove_all_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t message_id, 
    const u64_snowflake_t guild_id);
typedef void (message_reaction_remove_emoji_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t message_id, 
    const u64_snowflake_t guild_id,
    const struct discord_emoji *emoji);
typedef void (voice_state_update_cb)(
    struct discord *client, const struct discord_user *bot,
    const struct discord_voice_state *voice_state);
typedef void (voice_server_update_cb)(
    struct discord *client, const struct discord_user *bot,
    const char *token,
    const u64_snowflake_t guild_id,
    const char *endpoint);

struct discord_session {
  char url[MAX_URL_LEN];
  int shards;

  int total;
  int remaining;
  int reset_after;
  int max_concurrency; //max concurrent sessions we can handle

  int concurrent; //active concurrent sessions
  u64_unix_ms_t identify_tstamp; //identify timestamp in ms

  u64_unix_ms_t event_tstamp; //event timestamp in ms (resets every 60s)
  int event_count; //count elements to avoid reaching 120/60sec limit
};

struct discord_get_channel_messages_params {
  u64_snowflake_t around;
  u64_snowflake_t before;
  u64_snowflake_t after;
  int limit; // max number of messages (1-100)
};

/* default is application/json unless any multipart/form-data parameter is set */
struct discord_create_message_params {
  // common parameters
  char *content;
  char *nonce;
  bool tts;
  // parameters for application/json
  struct discord_embed *embed;
  struct discord_channel_allowed_mentions *allowed_mentions;
  struct discord_message_reference *message_reference;
  // parameters for multipart/form-data
  struct { // FILE STRUCT @todo better explanation
    char *name; //if only name is set, will search in working directory
    char *content; //the file contents
    size_t size; //the size must accompany the content
  } file;
  char *payload_json;
};

struct discord_edit_message_params {
  char *content;
  struct discord_embed *embed; //must be initialized
  enum discord_message_flags_code *flags;
  struct discord_channel_allowed_mentions *allowed_mentions; //must be initialized
};

struct discord_list_guild_members_params {
  int limit; // the number of members to return (1-1000)
  u64_snowflake_t after; // the highest user id in the previous page
};

 /* * * * * * * * * * * * * * * */
/* * * * CLIENT FUNCTIONS * * * */

void discord_global_init();
void discord_global_cleanup();

struct discord* discord_init(const char token[]);
struct discord* discord_config_init(const char config_file[]);
void discord_cleanup(struct discord *client);

void discord_add_intents(struct discord *client, enum discord_gateway_intents code);
void discord_set_prefix(struct discord *client, char *prefix);
void discord_on_command(struct discord *client, char *command, message_cb *callback);
void discord_on_event_raw(struct discord *client, event_raw_cb *callback);
void discord_on_idle(struct discord *client, idle_cb *callback);
void discord_on_guild_role_create(struct discord *client, guild_role_cb *callback);
void discord_on_guild_role_update(struct discord *client, guild_role_cb *callback);
void discord_on_guild_role_delete(struct discord *client, guild_role_delete_cb *callback);
void discord_on_guild_member_add(struct discord *client, guild_member_cb *callback);
void discord_on_guild_member_update(struct discord *client, guild_member_cb *callback);
void discord_on_guild_member_remove(struct discord *client, guild_member_remove_cb *callback);
void discord_on_guild_ban_add(struct discord *client, guild_ban_cb *callback);
void discord_on_guild_ban_remove(struct discord *client, guild_ban_cb *callback);
void discord_on_channel_create(struct discord *client, channel_cb *callback);
void discord_on_channel_update(struct discord *client, channel_cb *callback);
void discord_on_channel_delete(struct discord *client, channel_cb *callback);
void discord_on_channel_pins_update(struct discord *client, channel_pins_update_cb *callback);
void discord_on_message_create(struct discord *client, message_cb *callback);
void discord_on_sb_message_create(struct discord *client, sb_message_cb *callback);
void discord_on_message_update(struct discord *client, message_cb *callback);
void discord_on_sb_message_update(struct discord *client, sb_message_cb *callback);
void discord_on_message_delete(struct discord *client, message_delete_cb *callback);
void discord_on_message_delete_bulk(struct discord *client, message_delete_bulk_cb *callback);
void discord_on_message_reaction_add(struct discord *client, message_reaction_add_cb *callback);
void discord_on_message_reaction_remove(struct discord *client, message_reaction_remove_cb *callback);
void discord_on_message_reaction_remove_all(struct discord *client, message_reaction_remove_all_cb* callback);
void discord_on_message_reaction_remove_emoji(struct discord *client, message_reaction_remove_emoji_cb *callback);
void discord_on_voice_state_update(struct discord *client, voice_state_update_cb *callback);
void discord_on_voice_server_update(struct discord *client, voice_server_update_cb *callback);
void discord_on_ready(struct discord *client, idle_cb *callback);

void discord_run(struct discord *client);

void* discord_set_data(struct discord *client, void *data);
void* discord_get_data(struct discord *client);

void discord_replace_presence(struct discord *client, struct discord_gateway_status_update *presence);
void discord_set_presence(struct discord *client, struct discord_gateway_activity *activity, char status[], bool afk);
enum ws_status discord_gateway_status(struct discord *client);

/* * * * * * * * * * * * * * * * * * * * * */
/* * * * VOICE CONNECTIONS FUNCTIONS * * * */

void discord_send_voice_state_update(
  struct discord *client,
  u64_snowflake_t guild_id,
  u64_snowflake_t channel_id,
  bool self_mute,
  bool self_deaf,
  struct discord_voice *p_vc);
void discord_send_speaking(struct discord *client, struct discord_voice *vc, enum discord_voice_speaking_flags flag, int delay, int ssrc);
void discord_voice_connect(struct discord_voice *vc);


 /* * * * * * * * * * * * * * * * */
/* * * * ENDPOINT FUNCTIONS * * * */

// CHANNEL ENDPOINTS
void discord_get_channel(struct discord *client, const u64_snowflake_t channel_id, struct discord_channel *p_channel);
void discord_delete_channel(struct discord *client, const u64_snowflake_t channel_id, struct discord_channel *p_channel);
void discord_add_pinned_channel_message(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id);
void discord_delete_pinned_channel_message(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id);
void discord_get_channel_messages(struct discord *client, const u64_snowflake_t channel_id, struct discord_get_channel_messages_params *params, NTL_T(struct discord_message) *p_messages);
void discord_delete_message(struct discord *client, u64_snowflake_t channel_id, u64_snowflake_t message_id);
void discord_create_message(struct discord *client, const u64_snowflake_t channel_id, struct discord_create_message_params *params, struct discord_message *p_message);
void discord_edit_message(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, struct discord_edit_message_params *params, struct discord_message *p_message);
void discord_create_reaction(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, const u64_snowflake_t emoji_id, const char emoji_name[]);
void discord_delete_all_reactions(struct discord *client, u64_snowflake_t channel_id, u64_snowflake_t message_id);
void discord_delete_all_reactions_for_emoji(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, const u64_snowflake_t emoji_id, const char emoji_name[]);
void discord_trigger_typing_indicator(struct discord *client, const u64_snowflake_t channel_id);

// EMOJI ENDPOINTS
void discord_list_guild_emojis(struct discord *client, const u64_snowflake_t guild_id, NTL_T(struct discord_emoji) *p_emojis);

// GUILD ENDPOINTS
void discord_get_guild(struct discord *client, const u64_snowflake_t guild_id, struct discord_guild *p_guild);
void discord_get_guild_channels(struct discord *client, const u64_snowflake_t guild_id, NTL_T(struct discord_channel) *p_channels);
void discord_create_guild_channel(struct discord *client, const u64_snowflake_t guild_id, struct discord_create_guild_channel_params *params, struct discord_channel *p_channel);
void  discord_get_guild_member(struct discord *client, u64_snowflake_t guild_id, u64_snowflake_t user_id, struct discord_guild_member *p_member);
void discord_list_guild_members(struct discord *client, const u64_snowflake_t guild_id, struct discord_list_guild_members_params *params, NTL_T(struct discord_guild_member) *p_members);
void discord_modify_guild_member(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, struct discord_modify_guild_member_params *params, struct discord_guild_member *p_member);
void discord_remove_guild_member(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id);
void discord_get_guild_bans(struct discord *client, const u64_snowflake_t guild_id, NTL_T(struct discord_guild_ban) *p_bans);
void discord_get_guild_ban(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, struct discord_guild_ban *p_ban);
void discord_create_guild_ban(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, int delete_message_days, const char reason[]);
void discord_remove_guild_ban(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, const char reason[]);
void discord_get_guild_roles(struct discord *client, const u64_snowflake_t guild_id, NTL_T(struct discord_guild_role) *p_roles);
void discord_create_guild_role(struct discord *client, const u64_snowflake_t guild_id, struct discord_create_guild_role_params *params, struct discord_guild_role *p_role);
void discord_delete_guild_role(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t role_id);

// USER ENDPOINTS
void discord_get_user(struct discord *client, const u64_snowflake_t user_id, struct discord_user *p_user);
void discord_get_current_user(struct discord *client, struct discord_user *p_user);
void sb_discord_get_current_user(struct discord *client, struct sized_buffer *p_sb_user);
void discord_get_current_user_guilds(struct discord *client, NTL_T(struct discord_guild) *p_guilds);
void discord_leave_guild(struct discord *client, const u64_snowflake_t guild_id);

// GATEWAY ENDPOINTS
void discord_get_gateway(struct discord *client, struct discord_session *p_session);
void discord_get_gateway_bot(struct discord *client, struct discord_session *p_session);


/* * * * * * * * * * * * * * * * * * * */
/* * * * MISCELLANEOUS FUNCTIONS * * * */

// EMBED MISC
void discord_embed_set_thumbnail(struct discord_embed *embed, char url[], char proxy_url[], int height, int width);
void discord_embed_set_image(struct discord_embed *embed, char url[], char proxy_url[], int height, int width);
void discord_embed_set_video(struct discord_embed *embed, char url[], char proxy_url[], int height, int width);
void discord_embed_set_footer(struct discord_embed *embed, char text[], char icon_url[], char proxy_icon_url[]);
void discord_embed_set_provider(struct discord_embed *embed, char name[], char url[]);
void discord_embed_set_author(struct discord_embed *embed, char name[], char url[], char icon_url[], char proxy_icon_url[]);
void discord_embed_add_field(struct discord_embed *embed, char name[], char value[], bool Inline);

// CHANNEL MISC
void discord_overwrite_append(
  NTL_T(struct discord_channel_overwrite) *permission_overwrites, 
  u64_snowflake_t id, 
  int type, 
  enum discord_permissions_bitwise_flags allow, 
  enum discord_permissions_bitwise_flags deny);

void
discord_get_channel_at_pos(
  struct discord *client, 
  const u64_snowflake_t guild_id, 
  const enum discord_channel_types type,
  const size_t position,
  struct discord_channel *p_channel);

// MESSAGE MISC
void discord_delete_messages_by_author_id(
  struct discord *client,
  u64_snowflake_t channel_id,
  u64_snowflake_t author_id);

void discord_get_voice_connections(struct discord *client, NTL_T(struct discord_voice) *vcs);

#include "./specs-code/all_fun.h"

#endif // DISCORD_H
