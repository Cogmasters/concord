#ifndef DISCORD_H
#define DISCORD_H

#include <stdbool.h>
#include "json-actor-boxed.h"

/* FORWARD DECLARATIONS */
struct discord;

typedef uint64_t u64_unix_ms_t; // unix time in ms

/* SNOWFLAKES
https://discord.com/developers/docs/reference#snowflakes */
typedef uint64_t u64_snowflake_t; // discord's snowflake datatype
#define SNOWFLAKE_INCREMENT           12
#define SNOWFLAKE_PROCESS_ID          17
#define SNOWFLAKE_INTERNAL_WORKER_ID  22
#define SNOWFLAKE_TIMESTAMP           64

/* Size limits discovered from Discord docs and across the web */
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

/// @see specs/discord for generated code specs 
#include "specs-code/discord/all_opaque_struct.h"
#include "specs-code/discord/all_enums.h"
#include "specs-code/discord/all_structs.h"
#include "specs-code/discord/all_functions.h"


/** 
 * IDLE CALLBACK 
 * @note runs on every WebSockets loop iteration, no trigger required
 * @see discord_set_on_idle()
 */
typedef void (idle_cb)(struct discord *client, const struct discord_user *bot);

/**
 * RAW EVENT CALLBACK
 * @note if activated, the callback is triggered on every event detected.
 *        it is called after every "normal" callback, and it doesn't
 *        overwrite any existing callback
 * @see discord_set_on_raw_event()
 */
typedef void (event_raw_cb)(
    struct discord *client, 
    enum discord_gateway_events event, 
    struct sized_buffer *sb_bot, 
    struct sized_buffer *event_data);

/**
 * GUILD ROLE EVENTS CALLBACKS 
 * @see https://discord.com/developers/docs/topics/gateway#guilds 
 * @see discord_set_on_guild_xxx() 
 */
typedef void (guild_role_cb)(
    struct discord *client, const struct discord_user *bot,
    const u64_snowflake_t guild_id,
    const struct discord_guild_role *role);
typedef void (guild_role_delete_cb)(
    struct discord *client, const struct discord_user *bot,
    const u64_snowflake_t guild_id,
    const u64_snowflake_t role_id);

/**
 * GUILD MEMBER EVENTS CALLBACKS 
 * @see https://discord.com/developers/docs/topics/gateway#guilds 
 * @see discord_set_on_guild_member_xxx() 
 */
typedef void (guild_member_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t guild_id, 
    const struct discord_guild_member *member);
typedef void (guild_member_remove_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t guild_id, 
    const struct discord_user *user);

/**
 * GUILD BAN EVENTS CALLBACKS 
 * @see https://discord.com/developers/docs/topics/gateway#guilds 
 * @see discord_set_on_guild_ban_xxx() 
 */
typedef void (guild_ban_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t guild_id, 
    const struct discord_user *user);

/**
 * MESSAGE EVENTS CALLBACKS 
 * @see https://discord.com/developers/docs/topics/gateway#messages 
 * @see discord_set_on_message_xxx() 
 */
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

/**
 * CHANNEL EVENTS CALLBACKS 
 * @see https://discord.com/developers/docs/topics/gateway#channels 
 * @see discord_set_on_channel_xxx() 
 */
typedef void (channel_cb)(
    struct discord *client, const struct discord_user *bot, 
    const struct discord_channel *channel);
typedef void (channel_pins_update_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t guild_id,
    const u64_snowflake_t channel_id,
    const u64_unix_ms_t last_pin_timestamp);

/**
 * MESSAGE REACTION EVENTS CALLBACKS 
 * @see https://discord.com/developers/docs/topics/gateway#messages 
 * @see discord_set_on_message_reaction_xxx() 
 */
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

/**
 * VOICE EVENTS CALLBACKS 
 * @see https://discord.com/developers/docs/topics/gateway#voice
 * @see discord_set_on_voice_xxx() 
 */
typedef void (voice_state_update_cb)(
    struct discord *client, const struct discord_user *bot,
    const struct discord_voice_state *voice_state);
typedef void (voice_server_update_cb)(
    struct discord *client, const struct discord_user *bot,
    const char *token,
    const u64_snowflake_t guild_id,
    const char *endpoint);

struct discord_session {
  /// @todo this can become spec generated code
  /// @see https://discord.com/developers/docs/topics/gateway#get-gateway-bot-json-response
  // The WSS URL that can be used for connecting to the gateway
  char url[MAX_URL_LEN];
  // The recommended number of shards to use when connecting
  int shards;
  
  /// @todo this can become spec generated code
  /// @see https://discord.com/developers/docs/topics/gateway#session-start-limit-object
  // the total number of session starts the current user is allowed
  int total;
  // the remaining number of session starts the current user is allowed
  int remaining;
  // the number of milliseconds after which the limit resets
  int reset_after;
  // the number of identify requests allowed per 5 seconds
  int max_concurrency;

  // active concurrent sessions
  int concurrent;
  // timestamp of last succesful identify request
  u64_unix_ms_t identify_tstamp;

  // timestamp of last succesful event timestamp in ms (resets every 60s)
  u64_unix_ms_t event_tstamp;

  // event counter to avoid reaching limit of 120 events per 60 sec
  int event_count;
};

/// @todo this can become specs generated code
struct discord_get_channel_messages_params {
  u64_snowflake_t around;
  u64_snowflake_t before;
  u64_snowflake_t after;
  int limit; // max number of messages (1-100)
};

/**
 * @todo this can become specs generated code
 * @note by content-type sent is @b application/json, UNLESS any 
 *        @b multipart/form-data parameter is set */
struct discord_create_message_params {
  /// common to @b application/json and @b multipart/form-data parameters
  // the content of the message being sent
  char *content;
  // the nonce of the message being sent
  char *nonce;
  // enable/disable text-to-speech
  bool tts;
  
  /// parameters for @b application/json
  struct discord_embed *embed; /** @see specs-code/channel.objects.h and discord-misc.c */
  struct discord_channel_allowed_mentions *allowed_mentions; /** @see specs-code/channel.objects.h */
  struct discord_message_reference *message_reference; /** @see specs-code/channel.message.h */
  
  /// parameters for @b multipart/form-data
  /// @note if just name field is set, will search for file in working directory
  struct { // FILE STRUCT
    // the name of the file being sent
    char *name;
    // the contents and size of the file being sent (optional)
    char *content; /** @todo could be a struct sized_buffer */
    size_t size;
  } file;
  char *payload_json;
};

/// @todo this can become specs generated code
struct discord_edit_message_params {
  char *content;
  struct discord_embed *embed;
  enum discord_message_flags_code *flags;
  struct discord_channel_allowed_mentions *allowed_mentions;
};

/// @todo this can become specs generated code
struct discord_list_guild_members_params {
  // the number of members to return (1-1000)
  int limit;
  // the highest user id in the previous page
  u64_snowflake_t after;
};


 /* * * * * * * * * * * * * * * */
/* * * * CLIENT FUNCTIONS * * * */

/**
 * Initialize resources of globals used by discord.h
 */
void discord_global_init();

/**
 * Free resources of globals used by discord.h
 */
void discord_global_cleanup();

/**
 * Create a Discord Client handle by its token
 *
 * @param token the bot token
 * @return the newly created Discord Client handle
 */
struct discord* discord_init(const char token[]);

/**
 * Create a Discord Client handle by a bot.config file
 *
 * @param config_file the bot.config file name
 * @return the newly created Discord Client handle
 */
struct discord* discord_config_init(const char config_file[]);

/**
 * Free a Discord Client handle
 */
void discord_cleanup(struct discord *client);

/**
 * Subscribe to Discord Gateway events
 *
 * @see https://discord.com/developers/docs/topics/gateway#gateway-intents
 * @see specs/gateway.json and specs-code/gateway.h for definition
 *
 * @param client the client created with discord_init()
 * @param code the intents opcode
 *        @note can be set as a bitmask operation (ex: A | B | C)
 */
void discord_add_intents(struct discord *client, enum discord_gateway_intents code);

/**
 * Set a mandatory prefix set commands
 * ex: if a "help" command and a "!" prefix is set, the command will
 *        only be validated if its read as "!help"
 *
 * @param client the client created with discord_init()
 * @param prefix the prefix that should accompany any command
 *
 * @see discord_set_on_command()
 */
void discord_set_prefix(struct discord *client, char *prefix);

/**
 * Set command/callback pair, the call back is triggered if someone
 *        types the command in chat.
 * @note the command and any subjacent empty space is automatically 
 *        left out of the message->content received by the call back
 *
 * @param client the client created with discord_init()
 * @param command the command to trigger the callback
 * @param callback the callback to run when triggered by the command
 *
 * @see discord_set_prefix() for changing a command prefix
 */
void discord_set_on_command(struct discord *client, char *command, message_cb *callback);

/**
 * Set a callback that triggers a response for any event the client is
 *        subscribed to. The call back will be the last call back to be
 *        executed.
 * @note this gives the raw JSON payload associated with the event
 *
 * @param client the client created with discord_init()
 * @param callback the callback to run when any event is detected
 */
void discord_set_on_event_raw(struct discord *client, event_raw_cb *callback);

/**
 * Set a callback that triggers despite any event being detected. It
 *        is triggered every discord_gateway_run() event loop iteration.
 *
 * @param client the client created with discord_init()
 * @param callback the callback to run when triggered at every event loop iteration
 */
void discord_set_on_idle(struct discord *client, idle_cb *callback);

/**
 * The following functions can be used to assign a user-callback to
 *        execute when its corresponding events are detected. 
 * @note these functions will automatically set the necessary intent(s)
 *        @see discord_add_intents()
 *
 * @param client the client created with discord_init()
 * @param callback the callback to run when triggered by event
 */
void discord_set_on_guild_role_create(struct discord *client, guild_role_cb *callback);
void discord_set_on_guild_role_update(struct discord *client, guild_role_cb *callback);
void discord_set_on_guild_role_delete(struct discord *client, guild_role_delete_cb *callback);
void discord_set_on_guild_member_add(struct discord *client, guild_member_cb *callback);
void discord_set_on_guild_member_update(struct discord *client, guild_member_cb *callback);
void discord_set_on_guild_member_remove(struct discord *client, guild_member_remove_cb *callback);
void discord_set_on_guild_ban_add(struct discord *client, guild_ban_cb *callback);
void discord_set_on_guild_ban_remove(struct discord *client, guild_ban_cb *callback);
void discord_set_on_channel_create(struct discord *client, channel_cb *callback);
void discord_set_on_channel_update(struct discord *client, channel_cb *callback);
void discord_set_on_channel_delete(struct discord *client, channel_cb *callback);
void discord_set_on_channel_pins_update(struct discord *client, channel_pins_update_cb *callback);
void discord_set_on_message_create(struct discord *client, message_cb *callback);
void discord_set_on_sb_message_create(struct discord *client, sb_message_cb *callback);
void discord_set_on_message_update(struct discord *client, message_cb *callback);
void discord_set_on_sb_message_update(struct discord *client, sb_message_cb *callback);
void discord_set_on_message_delete(struct discord *client, message_delete_cb *callback);
void discord_set_on_message_delete_bulk(struct discord *client, message_delete_bulk_cb *callback);
void discord_set_on_message_reaction_add(struct discord *client, message_reaction_add_cb *callback);
void discord_set_on_message_reaction_remove(struct discord *client, message_reaction_remove_cb *callback);
void discord_set_on_message_reaction_remove_all(struct discord *client, message_reaction_remove_all_cb* callback);
void discord_set_on_message_reaction_remove_emoji(struct discord *client, message_reaction_remove_emoji_cb *callback);
void discord_set_on_ready(struct discord *client, idle_cb *callback);
void discord_set_on_voice_state_update(struct discord *client, voice_state_update_cb *callback);
void discord_set_on_voice_server_update(struct discord *client, voice_server_update_cb *callback);

/**
 * Start a connection to the Discord Gateway
 *
 * @param client the client created with discord_init()
 */
void discord_run(struct discord *client);

/**
 * Set a user arbitrary data, by associating it to the client
 * @note the user should provide his own locking mechanism to protect
 *        his data from race conditions
 *
 * @param client the client created with discord_init()
 * @param data user arbitrary data to be accessed via discord_get_data()
 * @return the arbitrary user data address
 * 
 * @see discord_get_data()
 */
void* discord_set_data(struct discord *client, void *data);

/**
 * Get a user arbitrary data associated to the client via discord_set_data()
 * @note the user should provide his own locking mechanism to protect
 *        his data from race conditions
 *
 * @param client the client created with discord_init()
 * @return the arbitrary user data address
 *
 * @see discord_set_data()
 */
void* discord_get_data(struct discord *client);

/**
 * Replace the Client presence with a struct discord_gateway_status_update
 * @note discord_set_presence() is a more comprehensible alternative
 *
 * @param client the client created with discord_init()
 * @param presence the presence to replace the client's
 *        @see specs/gateway.json and specs-code/gateway.h for definition
 *
 * @see discord_set_presence()
 */
void discord_replace_presence(struct discord *client, struct discord_gateway_status_update *presence);

/**
 * Modify the Client presence state
 *
 * @param client the client created with discord_init()
 * @param activity the user current activities
 *        @see specs/gateway.json and specs-code/gateway.h for definition
 * @param status either "idle","dnd","online", or "offline"
 * @param afk #true or #false
 */
void discord_set_presence(struct discord *client, struct discord_gateway_activity *activity, char status[], bool afk);


 /* * * * * * * * * * * * * * * * */
/* * * * ENDPOINT FUNCTIONS * * * */

// CHANNEL ENDPOINTS
void discord_get_channel(struct discord *client, const u64_snowflake_t channel_id, struct discord_channel *p_channel);
void discord_delete_channel(struct discord *client, const u64_snowflake_t channel_id, struct discord_channel *p_channel);
void discord_add_pinned_channel_message(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id);
void discord_delete_pinned_channel_message(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id);
void discord_get_channel_messages(struct discord *client, const u64_snowflake_t channel_id, struct discord_get_channel_messages_params *params, NTL_T(struct discord_message) *p_messages);
void discord_delete_message(struct discord *client, u64_snowflake_t channel_id, u64_snowflake_t message_id);
void discord_bulk_delete_messages(struct discord *client, u64_snowflake_t channel_id, NTL_T(u64_snowflake_t) messages);
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

#ifdef _DISCORD_ADD_ONS
#include "discord-voice-connections.h"
#endif

#endif // DISCORD_H
