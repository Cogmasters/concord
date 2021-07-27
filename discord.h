/**
 * @file discord.h
 * @author cee-studio
 * @date 27 Jul 2021
 * @brief File containing public functions and datatypes
 *
 * These symbols are organized in a intuitive fashion to be easily 
 * matched to the official Discord API docs.
 * @see https://discord.com/developers/docs/intro
 */

#ifndef DISCORD_H
#define DISCORD_H

#include <stdbool.h>
#include "json-actor-boxed.h"
#include "types.h"
#include "logconf.h"

#define DISCORD_API_BASE_URL "https://discord.com/api/v9"
#define DISCORD_GATEWAY_URL_SUFFIX "?v=9&encoding=json"
#define DISCORD_VOICE_CONNECTIONS_URL_SUFFIX "?v=4"

/* FORWARD DECLARATIONS */
struct discord;
struct discord_voice_cbs;

/** @defgroup Snowflake
 *  @see https://discord.com/developers/docs/reference#snowflakes
 *  @{ */
#define DISCORD_SNOWFLAKE_INCREMENT           12
#define DISCORD_SNOWFLAKE_PROCESS_ID          17
#define DISCORD_SNOWFLAKE_INTERNAL_WORKER_ID  22
#define DISCORD_SNOWFLAKE_TIMESTAMP           64
/** @} */

/** @defgroup GeneralLimits
 *  @{ */
#define DISCORD_MAX_NAME_LEN          100 + 1
#define DISCORD_MAX_TOPIC_LEN         1024 + 1
#define DISCORD_MAX_DESCRIPTION_LEN   2048 + 1
#define DISCORD_MAX_USERNAME_LEN      32 + 1
#define DISCORD_MAX_DISCRIMINATOR_LEN 4 + 1
#define DISCORD_MAX_REASON_LEN        512 + 1
#define DISCORD_MAX_MESSAGE_LEN       2000 + 1
#define DISCORD_MAX_PAYLOAD_LEN       4096 + 1
#define DISCORD_MAX_VOICE_CONNECTIONS 512
/** @} */

/** @defgroup EmbedLimits
 *  @see https://discord.com/developers/docs/resources/channel#embed-limits 
 *  @{ */
#define DISCORD_EMBED_TITLE_LEN       256 + 1
#define DISCORD_EMBED_DESCRIPTION_LEN 2048 + 1
#define DISCORD_EMBED_MAX_FIELDS      25
#define DISCORD_EMBED_FIELD_NAME_LEN  256 + 1
#define DISCORD_EMBED_FIELD_VALUE_LEN 1024 + 1
#define DISCORD_EMBED_FOOTER_TEXT_LEN 2048 + 1
#define DISCORD_EMBED_AUTHOR_NAME_LEN 256 + 1
/** @} */

/** @defgroup WebhookLimits
 *  @see https://discord.com/developers/docs/resources/webhook#create-webhook-json-params
 *  @{ */
#define DISCORD_WEBHOOK_NAME_LEN 80 + 1
/** @} */

// see specs/discord/ for specs
#include "specs-code/discord/all_opaque_struct.h"
#include "specs-code/discord/all_enums.h"
#include "specs-code/discord/all_structs.h"
#include "specs-code/discord/all_functions.h"


/**
 * @brief Event Handling Mode callback
 *
 * A very important callback that enables the user with a fine-grained control 
 * of how each event is handled: blocking, non-blocking or ignored
 *
 * @see discord_set_event_handler()
 * @see discord_gateway_events
 */
typedef enum discord_event_handling_mode (*discord_event_mode_cb)(struct discord *client, struct discord_user *bot, struct sized_buffer *event_data, enum discord_gateway_events event);

/** 
 * @brief Idle callback
 *
 * Runs on every WebSockets loop iteration, no trigger required
 * @see discord_set_on_idle()
 */
typedef void (*discord_idle_cb)(struct discord *client, const struct discord_user *bot);

/**
 * @brief Raw Event callback
 *
 * If activated, this callback is triggered on any event.
 * It is executed after every other callback has been checked.
 * @see discord_set_on_event_raw()
 */
typedef void (*discord_event_raw_cb)(
    struct discord *client, 
    enum discord_gateway_events event, 
    struct sized_buffer *sb_bot, 
    struct sized_buffer *event_data);

/**
 * @brief Guild Role Create/Update callback
 *
 * @see https://discord.com/developers/docs/topics/gateway#guilds 
 * @see discord_set_on_guild_role_create() 
 * @see discord_set_on_guild_role_update() 
 */
typedef void (*discord_guild_role_cb)(
    struct discord *client, const struct discord_user *bot,
    const u64_snowflake_t guild_id,
    const struct discord_permissions_role *role);
/**
 * @brief Guild Role Delete callback
 *
 * @see https://discord.com/developers/docs/topics/gateway#guilds 
 * @see discord_set_on_guild_role_delete() 
 */
typedef void (*discord_guild_role_delete_cb)(
    struct discord *client, const struct discord_user *bot,
    const u64_snowflake_t guild_id,
    const u64_snowflake_t role_id);

/**
 * @brief Guild Member Add/Update callback
 *
 * @see https://discord.com/developers/docs/topics/gateway#guilds 
 * @see discord_set_on_guild_member_add() 
 * @see discord_set_on_guild_member_update() 
 */
typedef void (*discord_guild_member_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t guild_id, 
    const struct discord_guild_member *member);
/**
 * @brief Guild Member Remove callback
 *
 * @see https://discord.com/developers/docs/topics/gateway#guilds 
 * @see discord_set_on_guild_member_remove() 
 */
typedef void (*discord_guild_member_remove_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t guild_id, 
    const struct discord_user *user);

/**
 * @brief Guild Ban Add/Remove callback
 *
 * @see https://discord.com/developers/docs/topics/gateway#guilds 
 * @see discord_set_on_guild_ban_add() 
 * @see discord_set_on_guild_ban_remove() 
 */
typedef void (*discord_guild_ban_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t guild_id, 
    const struct discord_user *user);

/**
 * @brief Message Create/Update callback
 *
 * @see https://discord.com/developers/docs/topics/gateway#messages 
 * @see discord_set_on_message_create() 
 * @see discord_set_on_message_update() 
 */
typedef void (*discord_message_cb)(
    struct discord *client, const struct discord_user *bot, 
    const struct discord_message *message);
typedef void (*discord_sb_message_cb)(
    struct discord *client, const struct discord_user *bot,
    struct sized_buffer *sb_bot,
    const struct discord_message *message,
    struct sized_buffer *msg_payload);

/**
 * @brief Message Delete callback
 *
 * @see https://discord.com/developers/docs/topics/gateway#messages 
 * @see discord_set_on_message_delete() 
 */
typedef void (*discord_message_delete_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t id, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t guild_id);
/**
 * @brief Message Delete Bulk callback
 *
 * @see https://discord.com/developers/docs/topics/gateway#messages 
 * @see discord_set_on_message_delete_bulk() 
 */
typedef void (*discord_message_delete_bulk_cb)(
    struct discord *client, const struct discord_user *bot, 
    const NTL_T(ja_u64) ids, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t guild_id);

/**
 * @brief Channel Create/Update/Delete callback
 *
 * @see https://discord.com/developers/docs/topics/gateway#channels 
 * @see discord_set_on_channel_create() 
 * @see discord_set_on_channel_update() 
 * @see discord_set_on_channel_delete() 
 */
typedef void (*discord_channel_cb)(
    struct discord *client, const struct discord_user *bot, 
    const struct discord_channel *channel);
/**
 * @brief Channel Pins Update callback
 *
 * @see https://discord.com/developers/docs/topics/gateway#channels 
 * @see discord_set_on_channel_pins_update() 
 */
typedef void (*discord_channel_pins_update_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t guild_id,
    const u64_snowflake_t channel_id,
    const u64_unix_ms_t last_pin_timestamp);

/**
 * @brief Message Reaction Add callback
 * @see https://discord.com/developers/docs/topics/gateway#messages 
 * @see discord_set_on_message_reaction_add() 
 */
typedef void (*discord_message_reaction_add_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t user_id,
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t message_id, 
    const u64_snowflake_t guild_id, 
    const struct discord_guild_member *member, 
    const struct discord_emoji *emoji);
/**
 * @brief Message Reaction Remove callback
 * @see https://discord.com/developers/docs/topics/gateway#messages 
 * @see discord_set_on_message_reaction_remove() 
 */
typedef void (*discord_message_reaction_remove_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t user_id,
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t message_id, 
    const u64_snowflake_t guild_id, 
    const struct discord_emoji *emoji);
/**
 * @brief Message Reaction Remove All callback
 * @see https://discord.com/developers/docs/topics/gateway#messages 
 * @see discord_set_on_message_reaction_remove_all() 
 */
typedef void (*discord_message_reaction_remove_all_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t message_id, 
    const u64_snowflake_t guild_id);
/**
 * @brief Message Reaction Remove Emoji callback
 * @see https://discord.com/developers/docs/topics/gateway#messages 
 * @see discord_set_on_message_reaction_remove_emoji() 
 */
typedef void (*discord_message_reaction_remove_emoji_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t message_id, 
    const u64_snowflake_t guild_id,
    const struct discord_emoji *emoji);

/**
 * @brief Voice State Update callback
 * @see https://discord.com/developers/docs/topics/gateway#voice
 * @see discord_set_on_voice_state_update() 
 */
typedef void (*discord_voice_state_update_cb)(
    struct discord *client, const struct discord_user *bot,
    const struct discord_voice_state *voice_state);
/**
 * @brief Voice Server Update callback
 * @see https://discord.com/developers/docs/topics/gateway#voice
 * @see discord_set_on_voice_server_update() 
 */
typedef void (*discord_voice_server_update_cb)(
    struct discord *client, const struct discord_user *bot,
    const char *token,
    const u64_snowflake_t guild_id,
    const char *endpoint);

/**
 * @todo make this specs generated code
 * @see https://discord.com/developers/docs/topics/gateway#get-gateway-bot-json-response
 * @see https://discord.com/developers/docs/topics/gateway#session-start-limit-object
 */
struct discord_session {
  char url[1024]; ///< The WSS URL that can be used for connecting to the gateway
  int shards; ///< The recommended number of shards to use when connecting
  
  int total; ///< the total number of session starts the current user is allowed
  int remaining; ///< the remaining number of session starts the current user is allowed
  int reset_after; ///< the number of milliseconds after which the limit resets
  int max_concurrency; ///< the number of identify requests allowed per 5 seconds

  int concurrent; ///< active concurrent sessions
  u64_unix_ms_t identify_tstamp; ///< timestamp of last succesful identify request

  u64_unix_ms_t event_tstamp; ///< timestamp of last succesful event timestamp in ms (resets every 60s)

  int event_count; ///< event counter to avoid reaching limit of 120 events per 60 sec
};

/**
 * @todo make this specs generated code
 */
struct discord_get_channel_messages_params {
  u64_snowflake_t around;
  u64_snowflake_t before;
  u64_snowflake_t after;
  int limit; // max number of messages (1-100)
};

/**
 * @todo make this specs generated code
 * @warning content-type sent is @p application/json, UNLESS any 
 *        @p multipart/form-data parameter is set
 */
struct discord_create_message_params {
  // common to @b application/json and @b multipart/form-data parameters
  char *content; ///< the content of the message being sent
  bool tts; ///< enable/disable text-to-speech
  
  // parameters for @b application/json
  NTL_T(struct discord_embed) embeds;
  struct discord_embed *embed; ///< deprecated
  struct discord_channel_allowed_mentions *allowed_mentions;
  struct discord_message_reference *message_reference;
  NTL_T(struct discord_component) components;
  
  // parameters for @b multipart/form-data
  // @note if just name field is set, will search for file in working directory
  struct { // FILE STRUCT
    char *name; ///< the name of the file being sent
    char *content; ///< the contents of the file being sent (optional)
    size_t size; ///< the size of the file being sent (if content is set)
  } file;
  char *payload_json;
};

/** 
 * @todo make this specs generated code
 */
struct discord_edit_message_params {
  char *content;
  struct discord_embed *embed;
  enum discord_message_flags_code *flags;
  struct discord_channel_allowed_mentions *allowed_mentions;
};

/**
 * @todo this can become specs generated code
 */
struct discord_list_guild_members_params {
  int limit; ///< the number of members to return (1-1000)
  u64_snowflake_t after; ///< the highest user id in the previous page
};


 /* * * * * * * * * * * * * * * */
/* * * * CLIENT FUNCTIONS * * * */

/**
 * @brief Initialize resources of globals used by discord.h
 */
void discord_global_init();

/**
 * @brief Free resources of globals used by discord.h
 */
void discord_global_cleanup();

/**
 * @brief Create a Discord Client handle by its token
 *
 * @param token the bot token
 * @return the newly created Discord Client handle
 */
struct discord* discord_init(const char token[]);

/**
 * @brief Create a Discord Client handle by a bot.config file
 *
 * @param config_file the bot.config file name
 * @return the newly created Discord Client handle
 */
struct discord* discord_config_init(const char config_file[]);

/**
 * @brief Free a Discord Client handle
 *
 * @param client the client created with discord_init()
 */
void discord_cleanup(struct discord *client);

/**
 * @brief Subscribe to Discord Gateway events
 *
 * @param client the client created with discord_init()
 * @param code the intents opcode, can be set as a bitmask operation (ex: A | B | C)
 * @see https://discord.com/developers/docs/topics/gateway#gateway-intents
 */
void discord_add_intents(struct discord *client, enum discord_gateway_intents code);

/**
 * @brief Unsubscribe from Discord Gateway events
 *
 * @param client the client created with discord_init()
 * @param code the intents opcode, can be set as a bitmask operation (ex: A | B | C)
 * @see https://discord.com/developers/docs/topics/gateway#gateway-intents
 *
 */
void discord_remove_intents(struct discord *client, enum discord_gateway_intents code);

/**
 * @brief Set a mandatory prefix before commands
 *
 * Example: If @a 'help' is a command and @a '!' prefix is set, the command will
 *        only be validated if @a '!help' is sent
 * @param client the client created with discord_init()
 * @param prefix the prefix that should accompany any command
 * @see discord_set_on_command()
 */
void discord_set_prefix(struct discord *client, char *prefix);

/**
 * @brief return value of discord_set_event_handler() callback
 *
 * @see discord_set_event_handler()
 */
enum discord_event_handling_mode {
  DISCORD_EVENT_IGNORE,  ///< this event has been handled
  DISCORD_EVENT_MAIN_THREAD, ///< handle this event in main thread
  DISCORD_EVENT_CHILD_THREAD ///< handle this event in a child thread
};

/**
 * @brief Specify how events should execute their callbacks, in a blocking or non-blocking fashion
 *
 * This is a very important function that provides the user a more fine-grained
 * control of the Discord Gateway's event-loop. By default, every event
 * callback will block the event-loop, but for a scalable bot application this
 * is undesirable. To circumvent this the user can specify which events
 * should be executed in parallel.
 *
 * In the following example code, a MESSAGE_CREATE event callback will be executed non-blocking and READY callback on the main thread, while
 * anything else will be ignored and won't be executed.
 *
 * @code{.c}
 * ...
 * enum discord_event_handling_mode
 * handle_events(
 *   struct discord *client,
 *   struct discord_user *bot,
 *   struct sized_buffer *event_data,
 *   enum discord_gateway_events event)
 * {
 *   switch (event) {
 *   case DISCORD_GATEWAY_EVENTS_READY:
 *      return DISCORD_EVENT_MAIN_THREAD;
 *   case DISCORD_GATEWAY_EVENTS_MESSAGE_CREATE:
 *      return DISCORD_EVENT_CHILD_THREAD;
 *   default:
 *      return DISCORD_EVENT_IGNORE;
 *   }
 * }
 *
 * int main()
 * {
 *   struct discord *client = discord_init(TOKEN);
 *
 *   discord_set_event_handler(client, &handle_events);
 *
 *   // The following will be executed on main thread
 *   discord_set_on_ready(client, &on_ready);
 *   // The following will be executed in another thread
 *   discord_set_on_message_create(client, &on_message_create);
 *   // The following will be ignored
 *   discord_set_on_message_delete(client, &on_message_delete);
 *   discord_set_on_channel_create(client, &on_channel_create);
 *
 *   discord_run(client);
 * }
 * @endcode
 *
 * @param client the client created_with discord_init()
 * @param fn the function that will be executed
 *
 * @warning The user is responsible for providing his own locking mechanism to avoid race-condition on sensitive data.
 * @see event_mode_cb
 * @see enum discord_event_handling_mode
 * @see enum discord_gateway_events
 */
void discord_set_event_handler(struct discord *client, discord_event_mode_cb fn);

/**
 * @brief Set command/callback pair, the callback is triggered if someone
 *        types command in chat.
 *
 * @param client the client created with discord_init()
 * @param command the command to trigger the callback
 * @param callback the callback that will be executed
 * @note The command and any subjacent empty space is left out of discord_message#content
 * @see discord_set_prefix() for changing a command prefix
 */
void discord_set_on_command(struct discord *client, char *command, discord_message_cb callback);

/**
 * @brief Set a callback that triggers on any event the client is subscribed to. 
 *
 * @note the callback will be executed last, after every other has been checked
 * @note this gives the raw JSON payload associated with the event
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 */
void discord_set_on_event_raw(struct discord *client, discord_event_raw_cb callback);

/**
 * @brief Set a callback that triggers at every event-loop iteration.
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 */
void discord_set_on_idle(struct discord *client, discord_idle_cb callback);

/**
 * @brief Set a callback that triggers when a guild role is created
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_guild_role_create(struct discord *client, discord_guild_role_cb callback);
/**
 * @brief Set a callback that triggers when a guild role is updated
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_guild_role_update(struct discord *client, discord_guild_role_cb callback);
/**
 * @brief Set a callback that triggers when a guild role is deleted
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_guild_role_delete(struct discord *client, discord_guild_role_delete_cb callback);
/**
 * @brief Set a callback that triggers when a guild member is added
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_guild_member_add(struct discord *client, discord_guild_member_cb callback);
/**
 * @brief Set a callback that triggers when a guild member is updated
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_guild_member_update(struct discord *client, discord_guild_member_cb callback);
/**
 * @brief Set a callback that triggers when a guild member is removed
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_guild_member_remove(struct discord *client, discord_guild_member_remove_cb callback);
/**
 * @brief Set a callback that triggers when a guild ban is added
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_guild_ban_add(struct discord *client, discord_guild_ban_cb callback);
/**
 * @brief Set a callback that triggers when a guild ban is removed
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_guild_ban_remove(struct discord *client, discord_guild_ban_cb callback);
/**
 * @brief Set a callback that triggers when a channel is created
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_channel_create(struct discord *client, discord_channel_cb callback);
/**
 * @brief Set a callback that triggers when a channel is updated
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_channel_update(struct discord *client, discord_channel_cb callback);
/**
 * @brief Set a callback that triggers when a channel is deleted
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_channel_delete(struct discord *client, discord_channel_cb callback);
/**
 * @brief Set a callback that triggers when some channel pins are updated
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_channel_pins_update(struct discord *client, discord_channel_pins_update_cb callback);
/**
 * @brief Set a callback that triggers when a message is created
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_message_create(struct discord *client, discord_message_cb callback);
void discord_set_on_sb_message_create(struct discord *client, discord_sb_message_cb callback);
/**
 * @brief Set a callback that triggers when a message is updated
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_message_update(struct discord *client, discord_message_cb callback);
void discord_set_on_sb_message_update(struct discord *client, discord_sb_message_cb callback);
/**
 * @brief Set a callback that triggers when a message is deleted
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_message_delete(struct discord *client, discord_message_delete_cb callback);
/*
 * @brief Set a callback that triggers when a bulk of messages are deleted
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_message_delete_bulk(struct discord *client, discord_message_delete_bulk_cb callback);
/**
 * @brief Set a callback that triggers when a message reaction is added
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_message_reaction_add(struct discord *client, discord_message_reaction_add_cb callback);
/**
 * @brief Set a callback that triggers when a message reaction is removed
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_message_reaction_remove(struct discord *client, discord_message_reaction_remove_cb callback);
/**
 * @brief Set a callback that triggers when all reaction from some message is removed
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_message_reaction_remove_all(struct discord *client, discord_message_reaction_remove_all_cb callback);
/**
 * @brief Set a callback that triggers when all instances of a particular reaction from some message is removed
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_message_reaction_remove_emoji(struct discord *client, discord_message_reaction_remove_emoji_cb callback);
/**
 * @brief Set a callback that triggers when the client is ready
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_ready(struct discord *client, discord_idle_cb callback);
/**
 * @brief Set a callback that triggers when a voice state is updated
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_voice_state_update(struct discord *client, discord_voice_state_update_cb callback);
/**
 * @brief Set a callback that triggers when a voice server is updated
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_voice_server_update(struct discord *client, discord_voice_server_update_cb callback);
/**
 * @brief Helper to quickly set voice callbacks
 *
 * @param client the client created with discord_init()
 * @param callbacks the voice callbacks that will be executed
 */
void discord_set_voice_cbs(struct discord *client, struct discord_voice_cbs *callbacks);

/**
 * @brief Start a connection to the Discord Gateway
 *
 * @param client the client created with discord_init()
 */
void discord_run(struct discord *client);

/**
 * @brief Keep some user arbitrary data, by associating it to the client
 *
 * @param client the client created with discord_init()
 * @param data user arbitrary data to be accessed via discord_get_data()
 * @return the arbitrary user data address
 * @warning the user should provide his own locking mechanism to protect
 *        his data from race conditions
 * @see discord_get_data()
 */
void* discord_set_data(struct discord *client, void *data);

/**
 * @brief Received user arbitrary data associated to the client
 *
 * @param client the client created with discord_init()
 * @return the arbitrary user data address
 * @warning the user should provide his own locking mechanism to protect
 *        his data from race conditions
 * @see discord_set_data()
 */
void* discord_get_data(struct discord *client);

/**
 * @brief Replace the Client presence with a struct discord_gateway_status_update
 *
 * @param client the client created with discord_init()
 * @param presence the presence to replace the client's
 * @note discord_set_presence() is a more comprehensible alternative
 * @see discord_set_presence()
 */
void discord_replace_presence(struct discord *client, struct discord_gateway_status_update *presence);

/**
 * @brief Modify the Client presence state
 *
 * @param client the client created with discord_init()
 * @param activity the user current activities
 * @param status either "idle","dnd","online", or "offline"
 * @param afk TRUE or FALSE
 */
void discord_set_presence(struct discord *client, struct discord_gateway_activity *activity, char status[], bool afk);


 /* * * * * * * * * * * * * * * * */
/* * * * ENDPOINT FUNCTIONS * * * */

/** @defgroup AuditLogEndpoints
 *  @{ */
/**
 * @brief @b GET /guilds/{guild.id}/audit-logs
 *
 * Returns an audit log object for the guild. 
 * @param client the client created with discord_init()
 * @param guild_id the guild to retrieve the audit log from
 * @param params request parameters
 * @param p_audit_log the audit log object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 * @note Requires the 'VIEW_AUDIT_LOG' permission
 * @see https://discord.com/developers/docs/resources/audit-log#get-guild-audit-log
 */
ORCAcode discord_get_guild_audit_log(struct discord *client, const u64_snowflake_t guild_id, struct discord_get_guild_audit_log_params *params, struct discord_audit_log *p_audit_log);
/** @} */

/** @defgroup ChannelEndpoints
 *  @{ */
/**
 * @brief @b GET /channels/{channel.id}
 *
 * Get a channel by ID. Returns a channel object. If the channel is a thread, a thread member object is included in the returned result.
 * @param client the client created with discord_init()
 * @param channel_id the channel to be retrieved
 * @param p_channel the channel object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 * @see https://discord.com/developers/docs/resources/channel#get-channel
 */
ORCAcode discord_get_channel(struct discord *client, const u64_snowflake_t channel_id, struct discord_channel *p_channel);
/**
 * @brief @b PATCH /channels/{channel.id}
 *
 * Update a channel's settings.
 * @param client the client created with discord_init()
 * @param channel_id the channel to be modified
 * @param params request parameters
 * @param p_channel the channel object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 * @see https://discord.com/developers/docs/resources/channel#modify-channel
 */
ORCAcode discord_modify_channel(struct discord *client, const u64_snowflake_t channel_id, struct discord_modify_channel_params *params, struct discord_channel *p_channel);
/**
 * @brief @b DELETE /channels/{channel.id}
 *
 * Delete a channel, or close a private message.
 * @param client the client created with discord_init()
 * @param channel_id the channel to be deleted
 * @param p_channel the channel object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 * @note Requires the MANAGE_CHANNELS permission for the guild, or MANAGE_THREADS if the channel is a thread. Deleting a category does not delete its child channels; they will have their parent_id removed and a Channel Update Gateway event will fire for each of them.
 * @note Fires a Channel Delete Gateway event (or Thread Delete if the channel was a thread).
 * @see https://discord.com/developers/docs/resources/channel#deleteclose-channel
 */
ORCAcode discord_delete_channel(struct discord *client, const u64_snowflake_t channel_id, struct discord_channel *p_channel);
/**
 * @brief @b GET /channels/{channel.id}/messages
 *
 * Returns the messages for a channel.
 * @param client the client created with discord_init()
 * @param channel_id the channel to get messages from
 * @param params request parameters
 * @param p_messages the null-terminated array of messages if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 * @note If operating on a guild channel, this endpoint requires the VIEW_CHANNEL permission to be present on the current user.
 * @note If the current user is missing the 'READ_MESSAGE_HISTORY' permission in the channel then this will return no messages (since they cannot read the message history).
 * @note The before, after, and around keys are mutually exclusive, only one may be passed at a time.
 * @see https://discord.com/developers/docs/resources/channel#get-channel-messages
 */
ORCAcode discord_get_channel_messages(struct discord *client, const u64_snowflake_t channel_id, struct discord_get_channel_messages_params *params, NTL_T(struct discord_message) *p_messages);
/**
 * @brief @b GET /channels/{channel.id}/messages/{message.id}
 *
 * Returns a specific message in the channel.
 * @param client the client created with discord_init()
 * @param channel_id the channel where the message resides
 * @param message_id the message itself
 * @param p_message the message object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 * @note If operating on a guild channel, this endpoint requires the 'READ_MESSAGE_HISTORY' permission to be present on the current user.
 * @see https://discord.com/developers/docs/resources/channel#get-channel-message
 */
ORCAcode discord_get_channel_message(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, struct discord_message *p_message);
/**
 * @brief @b POST /channels/{channel.id}/messages
 *
 * Post a message to a guild text or DM channel. Fires a Message Create Gateway event.
 * @param client the client created with discord_init()
 * @param channel_id the channel to send the message at
 * @param params request parameters
 * @param p_message the message object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 * @see https://discord.com/developers/docs/resources/channel#create-message
 */
ORCAcode discord_create_message(struct discord *client, const u64_snowflake_t channel_id, struct discord_create_message_params *params, struct discord_message *p_message);
/**
 * @brief @b POST /channels/{channel.id}/messages/{message.id}/crosspost
 *
 * Crosspost a message in a News Channel to following channels. This endpoint requires the 'SEND_MESSAGES' permission, if the current user sent the message, or additionally the 'MANAGE_MESSAGES' permission, for all other messages, to be present for the current user.
 * @param client the client created with discord_init()
 * @param channel_id the news channel that will crosspost
 * @param message_id the message that will crospost
 * @param p_message the message object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 * @see https://discord.com/developers/docs/resources/channel#crosspost-message
 */
ORCAcode discord_crosspost_message(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, struct discord_message *p_message);
/**
 * @brief @b PUT /channels/{channel.id}/messages/{message.id}/reactions/{emoji}/@me
 *
 * Create a reaction for the message.
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message to receive a reaction
 * @param emoji_id the emoji id (leave as 0 if not a custom emoji)
 * @param emoji_name the emoji name
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 * @see https://discord.com/developers/docs/resources/channel#create-reaction
 */
ORCAcode discord_create_reaction(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, const u64_snowflake_t emoji_id, const char emoji_name[]);
/**
 * @brief @b DELETE /channels/{channel.id}/messages/{message.id}/reactions/{emoji}/@me
 *
 * Delete a reaction the current user has made for the message.
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message to have a reaction deleted
 * @param emoji_id the emoji id (leave as 0 if not a custom emoji)
 * @param emoji_name the emoji name
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 * @see https://discord.com/developers/docs/resources/channel#delete-own-reaction
 */
ORCAcode discord_delete_own_reaction(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, const u64_snowflake_t emoji_id, const char emoji_name[]);
/**
 * @brief @b DELETE /channels/{channel.id}/messages/{message.id}/reactions/{emoji}/{user.id}
 *
 * Deletes another user's reaction.
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message to have a reaction deleted
 * @param user_id the user the reaction belongs to
 * @param emoji_id the emoji id (leave as 0 if not a custom emoji)
 * @param emoji_name the emoji name
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 * @see https://discord.com/developers/docs/resources/channel#delete-user-reaction
 */
ORCAcode discord_delete_user_reaction(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, const u64_snowflake_t user_id, const u64_snowflake_t emoji_id, const char emoji_name[]);
/**
 * @brief @b GET /channels/{channel.id}/messages/{message.id}/reactions/{emoji}
 *
 * Get a list of users that reacted with this emoji.
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message reacted to
 * @param emoji_id the emoji id (leave as 0 if not a custom emoji)
 * @param emoji_name the emoji name
 * @param params request parameters
 * @param p_users the null-terminated array of users if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 * @see https://discord.com/developers/docs/resources/channel#get-reactions
 */
ORCAcode discord_get_reactions(struct discord *client, u64_snowflake_t channel_id, u64_snowflake_t message_id, const u64_snowflake_t emoji_id, const char emoji_name[], struct discord_get_reactions_params *params, NTL_T(struct discord_user) *p_users);
/**
 * @brief @b DELETE /channels/{channel.id}/messages/{message.id}/reactions
 *
 * Deletes all reactions on a message.
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message that will be purged of reactions
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 * @see https://discord.com/developers/docs/resources/channel#delete-all-reactions
 */
ORCAcode discord_delete_all_reactions(struct discord *client, u64_snowflake_t channel_id, u64_snowflake_t message_id);
/**
 * @brief @b DELETE /channels/{channel.id}/messages/{message.id}/reactions/{emoji}
 *
 * Deletes all the reactions for a given emoji on a message.
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message that will be purged of reactions from particular emoji
 * @param emoji_id the emoji id (leave as 0 if not a custom emoji)
 * @param emoji_name the emoji name
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 * @see https://discord.com/developers/docs/resources/channel#delete-all-reactions-for-emoji
 */
ORCAcode discord_delete_all_reactions_for_emoji(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, const u64_snowflake_t emoji_id, const char emoji_name[]);
ORCAcode discord_edit_message(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, struct discord_edit_message_params *params, struct discord_message *p_message);
ORCAcode discord_delete_message(struct discord *client, u64_snowflake_t channel_id, u64_snowflake_t message_id);
ORCAcode discord_bulk_delete_messages(struct discord *client, u64_snowflake_t channel_id, NTL_T(u64_snowflake_t) messages);
ORCAcode discord_edit_channel_permissions(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t overwrite_id, struct discord_edit_channel_permissions_params *params);
ORCAcode discord_get_channel_invites(struct discord *client, const u64_snowflake_t channel_id, NTL_T(struct discord_invite) *p_invites);
ORCAcode discord_create_channel_invite(struct discord *client, const u64_snowflake_t channel_id, struct discord_create_channel_invite_params *params, struct discord_invite *p_invite);
ORCAcode discord_delete_channel_permission(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t overwrite_id);
ORCAcode discord_trigger_typing_indicator(struct discord* client, u64_snowflake_t channel_id);
ORCAcode discord_follow_news_channel(struct discord *client, const u64_snowflake_t channel_id, struct discord_follow_news_channel_params *params, struct discord_channel *p_followed_channel);
ORCAcode discord_get_pinned_messages(struct discord *client, const u64_snowflake_t channel_id, NTL_T(struct discord_message) *p_messages);
ORCAcode discord_pin_message(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id);
ORCAcode discord_unpin_message(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id);
ORCAcode discord_group_dm_add_recipient(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t user_id, struct discord_group_dm_add_recipient_params *params);
ORCAcode discord_group_dm_remove_recipient(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t user_id);
ORCAcode discord_start_thread_with_message(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, struct discord_start_thread_with_message_params *params, struct discord_channel *p_channel);
ORCAcode discord_start_thread_without_message(struct discord *client, const u64_snowflake_t channel_id, struct discord_start_thread_without_message_params *params, struct discord_channel *p_channel);
ORCAcode discord_join_thread(struct discord *client, const u64_snowflake_t channel_id);
ORCAcode discord_add_thread_member(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t user_id);
ORCAcode discord_leave_thread(struct discord *client, const u64_snowflake_t channel_id);
ORCAcode discord_remove_thread_member(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t user_id);
ORCAcode discord_list_thread_members(struct discord *client, const u64_snowflake_t channel_id, NTL_T(struct discord_thread_member) *p_thread_members);
ORCAcode discord_list_active_threads(struct discord *client, const u64_snowflake_t channel_id, struct discord_thread_response_body *body);
ORCAcode discord_list_public_archived_threads(struct discord *client, const u64_snowflake_t channel_id, const u64_unix_ms_t before, const int limit, struct discord_thread_response_body *body);
ORCAcode discord_list_private_archived_threads(struct discord *client, const u64_snowflake_t channel_id, const u64_unix_ms_t before, const int limit, struct discord_thread_response_body *body);
ORCAcode discord_list_joined_private_archived_threads(struct discord *client, const u64_snowflake_t channel_id, const u64_unix_ms_t before, const int limit, struct discord_thread_response_body *body);
/** @} */

/** @defgroup EmojiEndpoints
 *  @{ */
ORCAcode discord_list_guild_emojis(struct discord *client, const u64_snowflake_t guild_id, NTL_T(struct discord_emoji) *p_emojis);
ORCAcode discord_get_guild_emoji(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t emoji_id, struct discord_emoji *p_emoji);
ORCAcode discord_create_guild_emoji(struct discord *client, const u64_snowflake_t guild_id, struct discord_create_guild_emoji_params *params, struct discord_emoji *p_emoji);
ORCAcode discord_modify_guild_emoji(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t emoji_id, struct discord_modify_guild_emoji_params *params, struct discord_emoji *p_emoji);
ORCAcode discord_delete_guild_emoji(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t emoji_id);
/** @} */

/** @defgroup GuildEndpoints
 *  @{ */
ORCAcode discord_create_guild(struct discord *client, struct discord_create_guild_params *params, struct discord_guild *p_guild);
ORCAcode discord_get_guild(struct discord *client, const u64_snowflake_t guild_id, struct discord_guild *p_guild);
ORCAcode discord_get_guild_preview(struct discord *client, const u64_snowflake_t guild_id, struct discord_guild_preview *p_guild_preview);
ORCAcode discord_modify_guild(struct discord *client, const u64_snowflake_t guild_id, struct discord_modify_guild_params *params, struct discord_guild *p_guild);
ORCAcode discord_delete_guild(struct discord *client, const u64_snowflake_t guild_id);
ORCAcode discord_get_guild_channels(struct discord *client, const u64_snowflake_t guild_id, NTL_T(struct discord_channel) *p_channels);
ORCAcode discord_create_guild_channel(struct discord *client, const u64_snowflake_t guild_id, struct discord_create_guild_channel_params *params, struct discord_channel *p_channel);
ORCAcode discord_modify_guild_channel_positions(struct discord *client, const u64_snowflake_t guild_id, NTL_T(struct discord_modify_guild_channel_positions_params) params);
ORCAcode  discord_get_guild_member(struct discord *client, u64_snowflake_t guild_id, u64_snowflake_t user_id, struct discord_guild_member *p_member);
ORCAcode discord_list_guild_members(struct discord *client, const u64_snowflake_t guild_id, struct discord_list_guild_members_params *params, NTL_T(struct discord_guild_member) *p_members);
ORCAcode discord_search_guild_members(struct discord *client, const u64_snowflake_t guild_id, struct discord_search_guild_members_params *params, NTL_T(struct discord_guild_member) *p_members);
ORCAcode discord_modify_guild_member(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, struct discord_modify_guild_member_params *params, struct discord_guild_member *p_member);
ORCAcode discord_add_guild_member(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, struct discord_add_guild_member_params *params, struct discord_guild_member *p_member);
ORCAcode discord_modify_current_user_nick(struct discord *client, const u64_snowflake_t guild_id, const char nick[]);
ORCAcode discord_add_guild_member_role(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, const u64_snowflake_t role_id);
ORCAcode discord_remove_guild_member_role(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, const u64_snowflake_t role_id);
ORCAcode discord_remove_guild_member(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id);
ORCAcode discord_get_guild_bans(struct discord *client, const u64_snowflake_t guild_id, NTL_T(struct discord_guild_ban) *p_bans);
ORCAcode discord_get_guild_ban(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, struct discord_guild_ban *p_ban);
ORCAcode discord_create_guild_ban(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, int delete_message_days, const char reason[]);
ORCAcode discord_remove_guild_ban(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, const char reason[]);
ORCAcode discord_get_guild_roles(struct discord *client, const u64_snowflake_t guild_id, NTL_T(struct discord_permissions_role) *p_roles);
ORCAcode discord_create_guild_role(struct discord *client, const u64_snowflake_t guild_id, struct discord_create_guild_role_params *params, struct discord_permissions_role *p_role);
ORCAcode discord_modify_guild_role_positions(struct discord *client, const u64_snowflake_t guild_id, NTL_T(struct discord_modify_guild_role_positions_params) params, NTL_T(struct discord_permissions_role) *p_roles);
ORCAcode discord_modify_guild_role(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t role_id, struct discord_modify_guild_role_params *params, struct discord_permissions_role *p_role);
ORCAcode discord_delete_guild_role(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t role_id);
/** @} */

/** @defgroup InviteEndpoints
 *  @{ */
ORCAcode discord_get_invite(struct discord *client, char *invite_code, struct discord_get_invite_params *params, struct discord_invite *p_invite);
ORCAcode discord_delete_invite(struct discord *client, char *invite_code, struct discord_invite *p_invite);
/** @} */

/** @defgroup UserEndpoints
 *  @{ */
ORCAcode discord_get_user(struct discord *client, const u64_snowflake_t user_id, struct discord_user *p_user);
ORCAcode discord_modify_current_user(struct discord *client, struct discord_modify_current_user_params *params, struct discord_user *p_user);
ORCAcode discord_get_current_user(struct discord *client, struct discord_user *p_user);
ORCAcode sb_discord_get_current_user(struct discord *client, struct sized_buffer *p_sb_user);
ORCAcode discord_get_current_user_guilds(struct discord *client, NTL_T(struct discord_guild) *p_guilds);
ORCAcode discord_leave_guild(struct discord *client, const u64_snowflake_t guild_id);
ORCAcode discord_create_dm(struct discord *client, const u64_snowflake_t recipient_id, struct discord_channel *p_dm_channel);
ORCAcode discord_create_group_dm(struct discord *client, struct discord_create_group_dm_params *params, struct discord_channel *p_dm_channel);
ORCAcode discord_get_user_connections(struct discord *client, NTL_T(struct discord_connection) *p_connections);
/** @} */

/** @defgroup VoiceEndpoints
 *  @{ */
ORCAcode discord_list_voice_regions(struct discord *client, NTL_T(struct discord_voice_region) *p_voice_regions);
/** @} */

/** @defgroup GatewayEndpoints
 *  @{ */
ORCAcode discord_get_gateway(struct discord *client, struct discord_session *p_session);
ORCAcode discord_get_gateway_bot(struct discord *client, struct discord_session *p_session);
/** @} */


/* * * * * * * * * * * * * * * * * * * */
/* * * * MISCELLANEOUS FUNCTIONS * * * */

/** @defgroup EmbedMisc
 *  @{ */
void discord_embed_set_thumbnail(struct discord_embed *embed, char url[], char proxy_url[], int height, int width);
void discord_embed_set_image(struct discord_embed *embed, char url[], char proxy_url[], int height, int width);
void discord_embed_set_video(struct discord_embed *embed, char url[], char proxy_url[], int height, int width);
void discord_embed_set_footer(struct discord_embed *embed, char text[], char icon_url[], char proxy_icon_url[]);
void discord_embed_set_provider(struct discord_embed *embed, char name[], char url[]);
void discord_embed_set_author(struct discord_embed *embed, char name[], char url[], char icon_url[], char proxy_icon_url[]);
void discord_embed_set_title(struct discord_embed *embed, char format[], ...);
void discord_embed_add_field(struct discord_embed *embed, char name[], char value[], bool Inline);
/** @} */

/** @defgroup ChannelMisc
 *  @{ */
void discord_overwrite_append(NTL_T(struct discord_channel_overwrite) *permission_overwrites, u64_snowflake_t id, int type, enum discord_permissions_bitwise_flags allow, enum discord_permissions_bitwise_flags deny);
ORCAcode discord_get_channel_at_pos(struct discord *client, const u64_snowflake_t guild_id, const enum discord_channel_types type, const size_t position, struct discord_channel *p_channel);
ORCAcode discord_delete_messages_by_author_id(struct discord *client, u64_snowflake_t channel_id, u64_snowflake_t author_id);
/** @} */

/** @defgroup GuildMisc
 *  @{ */
ORCAcode discord_disconnect_guild_member(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, struct discord_guild_member *p_member);
/** @} */

#endif // DISCORD_H
