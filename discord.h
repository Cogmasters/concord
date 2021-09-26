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

/** @defgroup DiscordLimitsSnowflake
 *  @see https://discord.com/developers/docs/reference#snowflakes
 *  @{ */
#define DISCORD_SNOWFLAKE_INCREMENT           12
#define DISCORD_SNOWFLAKE_PROCESS_ID          17
#define DISCORD_SNOWFLAKE_INTERNAL_WORKER_ID  22
#define DISCORD_SNOWFLAKE_TIMESTAMP           64
/** @} DiscordLimitsSnowflake */

/** @defgroup DiscordLimitsGeneral
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
/** @} DiscordLimitsGeneral */

/** @defgroup DiscordLimitsEmbed
 *  @see https://discord.com/developers/docs/resources/channel#embed-limits 
 *  @{ */
#define DISCORD_EMBED_TITLE_LEN       256 + 1
#define DISCORD_EMBED_DESCRIPTION_LEN 2048 + 1
#define DISCORD_EMBED_MAX_FIELDS      25
#define DISCORD_EMBED_FIELD_NAME_LEN  256 + 1
#define DISCORD_EMBED_FIELD_VALUE_LEN 1024 + 1
#define DISCORD_EMBED_FOOTER_TEXT_LEN 2048 + 1
#define DISCORD_EMBED_AUTHOR_NAME_LEN 256 + 1
/** @} DiscordLimitsEmbed */

/** @defgroup DiscordLimitsWebhook
 *  @see https://discord.com/developers/docs/resources/webhook#create-webhook-json-params
 *  @{ */
#define DISCORD_WEBHOOK_NAME_LEN 80 + 1
/** @} DiscordLimitsWebhook */

// see specs/discord/ for specs
#include "specs-code/discord/one-specs.h"

/** @defgroup DiscordCallbacksGeneral
 *  @brief General-purpose callbacks
 *  @{ */
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
/** @} DiscordCallbacksGeneral */

/** @defgroup DiscordCallbacksApplicationCommand
 *  @brief Application Command event callbacks
 *  @see https://discord.com/developers/docs/topics/gateway#commands 
 *  @{ */
/**
 * @brief Application Command Create/Update/Delete callback
 *
 * @see discord_set_on_application_command_create() 
 *      discord_set_on_application_command_update() 
 *      discord_set_on_application_command_delete() 
 */
typedef void (*discord_application_command_cb)(
    struct discord *client, const struct discord_user *bot,
    const struct discord_application_command *app_cmd);
/** @} DiscordCallbacksApplicationCommand */

/** @defgroup DiscordCallbacksChannel
 *  @brief Channel-event callbacks
 *  @see https://discord.com/developers/docs/topics/gateway#channels 
 *  @{ */
/**
 * @brief Channel/Thread Create/Update/Delete callback
 *
 * @see discord_set_on_channel_create() 
 *      discord_set_on_channel_update() 
 *      discord_set_on_channel_delete() 
 *      discord_set_on_thread_create() 
 *      discord_set_on_thread_update() 
 *      discord_set_on_thread_delete() 
 */
typedef void (*discord_channel_cb)(
    struct discord *client, const struct discord_user *bot, 
    const struct discord_channel *channel);
/**
 * @brief Channel Pins Update callback
 *
 * @see discord_set_on_channel_pins_update() 
 */
typedef void (*discord_channel_pins_update_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t guild_id,
    const u64_snowflake_t channel_id,
    const u64_unix_ms_t last_pin_timestamp);
/** @} DiscordCallbacksChannel */

/** @defgroup DiscordCallbacksGuild
 *  @brief Guild-event callbacks
 *  @see https://discord.com/developers/docs/topics/gateway#guilds 
 *  @{ */
/**
 * @brief Guild Role Create/Update callback
 * @see discord_set_on_guild_role_create() 
 * @see discord_set_on_guild_role_update() 
 */
typedef void (*discord_guild_role_cb)(
    struct discord *client, const struct discord_user *bot,
    const u64_snowflake_t guild_id,
    const struct discord_role *role);
/**
 * @brief Guild Role Delete callback
 * @see discord_set_on_guild_role_delete() 
 */
typedef void (*discord_guild_role_delete_cb)(
    struct discord *client, const struct discord_user *bot,
    const u64_snowflake_t guild_id,
    const u64_snowflake_t role_id);

/**
 * @brief Guild Member Add/Update callback
 * @see discord_set_on_guild_member_add() 
 * @see discord_set_on_guild_member_update() 
 */
typedef void (*discord_guild_member_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t guild_id, 
    const struct discord_guild_member *member);
/**
 * @brief Guild Member Remove callback
 * @see discord_set_on_guild_member_remove() 
 */
typedef void (*discord_guild_member_remove_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t guild_id, 
    const struct discord_user *user);

/**
 * @brief Guild Ban Add/Remove callback
 * @see discord_set_on_guild_ban_add() 
 * @see discord_set_on_guild_ban_remove() 
 */
typedef void (*discord_guild_ban_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t guild_id, 
    const struct discord_user *user);
/** @} DiscordCallbacksGuild */

/** @defgroup DiscordCallbacksInteraction
 *  @brief Interaction-event callbacks
 *  @see https://discord.com/developers/docs/topics/gateway#interactions
 *  @{ */
/**
 * @brief Interaction Create callback
 * @see discord_set_on_interaction_create() 
 */
typedef void (*discord_interaction_cb)(
    struct discord *client, const struct discord_user *bot,
    const struct discord_interaction *interaction);
/** @} DiscordCallbacksInteraction */

/** @defgroup DiscordCallbacksMessage
 *  @brief Message-event callbacks
 *  @see https://discord.com/developers/docs/topics/gateway#messages 
 *  @{ */
/**
 * @brief Message Create/Update callback
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
 * @see discord_set_on_message_delete() 
 */
typedef void (*discord_message_delete_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t id, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t guild_id);
/**
 * @brief Message Delete Bulk callback
 * @see discord_set_on_message_delete_bulk() 
 */
typedef void (*discord_message_delete_bulk_cb)(
    struct discord *client, const struct discord_user *bot, 
    const NTL_T(ja_u64) ids, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t guild_id);

/**
 * @brief Message Reaction Add callback
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
 * @see discord_set_on_message_reaction_remove_all() 
 */
typedef void (*discord_message_reaction_remove_all_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t message_id, 
    const u64_snowflake_t guild_id);
/**
 * @brief Message Reaction Remove Emoji callback
 * @see discord_set_on_message_reaction_remove_emoji() 
 */
typedef void (*discord_message_reaction_remove_emoji_cb)(
    struct discord *client, const struct discord_user *bot, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t message_id, 
    const u64_snowflake_t guild_id,
    const struct discord_emoji *emoji);
/** @} DiscordCallbacksMessage */

/** @defgroup DiscordCallbacksVoice
 *  @brief Voice-event callbacks
 *  @see https://discord.com/developers/docs/topics/gateway#voice
 *  @{ */
/**
 * @brief Voice State Update callback
 * @see discord_set_on_voice_state_update() 
 */
typedef void (*discord_voice_state_update_cb)(
    struct discord *client, const struct discord_user *bot,
    const struct discord_voice_state *voice_state);
/**
 * @brief Voice Server Update callback
 * @see discord_set_on_voice_server_update() 
 */
typedef void (*discord_voice_server_update_cb)(
    struct discord *client, const struct discord_user *bot,
    const char *token,
    const u64_snowflake_t guild_id,
    const char *endpoint);
/** @} DiscordCallbacksVoice */


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
 * @brief Return the meaning of ORCAcode
 * @note if the client parameter is provided, the raw JSON error string will be given for ORCA_DISCORD_JSON_CODE code
 * @param code the ORCAcode to be explained
 * @param client the client created with discord_init(), NULL for generic error descriptions
 * @return a string containing the code meaning
 */
const char* discord_strerror(ORCAcode code, struct discord *client);

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
 * @brief Clone a discord client
 *
 * This is useful in a multithreading scenario. For example, making
 *        sure each client instance has its own shared url, headers,
 *        return codes.
 * @param orig_client the original client created with discord_init()
 * @return the original client clone
 */
struct discord* discord_clone(const struct discord *orig_client);

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
 * @brief Set a callback that triggers when the client is ready
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_ready(struct discord *client, discord_idle_cb callback);
/**
 * @brief Set a callback that triggers when a applicat command is created
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 */
void discord_set_on_application_command_create(struct discord *client, discord_application_command_cb callback);
/**
 * @brief Set a callback that triggers when a applicat command is updated
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 */
void discord_set_on_application_command_update(struct discord *client, discord_application_command_cb callback);
/**
 * @brief Set a callback that triggers when a applicat command is deleted
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 */
void discord_set_on_application_command_delete(struct discord *client, discord_application_command_cb callback);
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
 * @brief Set a callback that triggers when a thread is created
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_thread_create(struct discord *client, discord_channel_cb callback);
/**
 * @brief Set a callback that triggers when a thread is updated
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_thread_update(struct discord *client, discord_channel_cb callback);
/**
 * @brief Set a callback that triggers when a thread is deleted
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 * @note this function will automatically set intent(s) to make the callback triggerable
 */
void discord_set_on_thread_delete(struct discord *client, discord_channel_cb callback);
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
 * @brief Set a callback that triggers when a interaction is created
 *
 * @param client the client created with discord_init()
 * @param callback the callback that will be executed
 */
void
discord_set_on_interaction_create(struct discord *client, discord_interaction_cb callback);
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
 * @return ORCAcode for how the run went, ORCA_OK means nothing out of the ordinary
 */
ORCAcode discord_run(struct discord *client);

/**
 * @brief Gracefully shutdown a ongoing Discord connection
 *
 * @param client the client created with discord_init()
 */
void discord_shutdown(struct discord *client);

/**
 * @brief Gracefully reconnects a ongoing Discord connection
 *
 * @param client the client created with discord_init()
 * @param resume true to attempt to resume to previous session,
 *        false restart a fresh session
 */
void discord_reconnect(struct discord *client, bool resume);

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
 * @brief Set the Client presence state
 *
 * @param client the client created with discord_init()
 * @param presence overwrite client's presence with it
 * @see discord_presence_add_activity()
 */
void discord_set_presence(struct discord *client, struct discord_presence_status *presence);


 /* * * * * * * * * * * * * * * * */
/* * * * ENDPOINT FUNCTIONS * * * */

/** @defgroup DiscordGetGlobalApplicationCommands 
 * @brief @b GET /applications/{application.id}/commands
 *
 * Fetch all of the global commands for your application. Returns an array of application command objects.
 * @see https://discord.com/developers/docs/interactions/application-commands#get-global-application-commands
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param p_app_cmds the null-terminated array of application command objects if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_get_global_application_commands(struct discord *client, const u64_snowflake_t application_id, NTL_T(struct discord_application_command) *p_app_cmds);
/** @} DiscordGetGlobalApplicationCommands */

/** @defgroup DiscordCreateGlobalApplicationCommand 
 * @brief @b POST /applications/{application.id}/commands
 *
 * Create a new global command. New global commands will be available in all guilds after 1 hour.
 * @see https://discord.com/developers/docs/interactions/application-commands#create-global-application-command
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param params request parameters
 * @param p_app_cmd the application command object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_create_global_application_command(struct discord *client, const u64_snowflake_t application_id, struct discord_create_global_application_command_params *params, struct discord_application_command *p_app_cmd);
/// @struct discord_create_global_application_command_params
/** @} DiscordCreateGlobalApplicationCommand */

/** @defgroup DiscordGetGlobalApplicationCommand
 * @brief @b GET /applications/{application.id}/commands/{command.id}
 *
 * Fetch a global command for your application. Returns an application command object.
 * @see https://discord.com/developers/docs/interactions/application-commands#get-global-application-command
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param command_id the registered command id
 * @param p_app_cmd the application command object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_get_global_application_command(struct discord *client, const u64_snowflake_t application_id, const u64_snowflake_t command_id, struct discord_application_command *p_app_cmd);
/** @} DiscordGetGlobalApplicationCommand */

/** @defgroup DiscordEditGlobalApplicationCommand
 * @brief @b PATCH /applications/{application.id}/commands/{command.id}
 *
 * Edit a global command. Updates will be available in all guilds 
 * after 1 hour. Returns an application command object.
 * @see https://discord.com/developers/docs/interactions/application-commands#edit-global-application-command
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param command_id the registered command id
 * @param params request parameters
 * @param p_app_cmd the application command object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_edit_global_application_command(struct discord *client, const u64_snowflake_t application_id, const u64_snowflake_t command_id, struct discord_edit_global_application_command_params *params, struct discord_application_command *p_app_cmd);
/// @struct discord_edit_global_application_command_params
/** @} DiscordEditGlobalApplicationCommand */

/** @defgroup DiscordDeleteGlobalApplicationCommand
 * @brief @b DELETE /applications/{application.id}/commands/{command.id}
 *
 * Deletes a global command.
 * @see https://discord.com/developers/docs/interactions/application-commands#delete-global-application-command
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param command_id the registered command id
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_delete_global_application_command(struct discord *client, const u64_snowflake_t application_id, const u64_snowflake_t command_id);
/** @} DiscordDeleteGlobalApplicationCommand */

/** @defgroup DiscordBulkOverwriteGlobalApplicationCommand
 * @brief @b PUT /applications/{application.id}/commands
 *
 * Takes a list of application commands, overwriting existing commands 
 * that are registered globally for this application. Updates will be 
 * available in all guilds after 1 hour. Returns a list of application 
 * command objects. Commands that do not already exist will count 
 * toward daily application command create limits.
 * @see https://discord.com/developers/docs/interactions/application-commands#bulk-overwrite-global-application-commands
 * @warning This will overwrite all types of application commands: slash commands, user commands, and message commands.
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param params the request parameters, a list of application commands
 * @param p_app_cmds the null-terminated array of application command objects if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_bulk_overwrite_global_application_command(struct discord *client, const u64_snowflake_t application_id, NTL_T(struct discord_application_command) params, NTL_T(struct discord_application_command) *p_app_cmds);
/** @} DiscordBulkOverwriteGlobalApplicationCommand */

/** @defgroup DiscordGetGuildApplicationCommands 
 * @brief @b GET /applications/{application.id}/guilds/{guilds.id}/commands
 *
 * Fetch all of the guild commands for your application for a specific guild. Returns an array of application command objects.
 * @see https://discord.com/developers/docs/interactions/application-commands#get-guild-application-commands
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the commands are located
 * @param p_app_cmds the null-terminated array of application command objects if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_get_guild_application_commands(struct discord *client, const u64_snowflake_t application_id, const u64_snowflake_t guild_id, NTL_T(struct discord_application_command) *p_app_cmds);
/** @} DiscordGetGuildApplicationCommands */

/** @defgroup DiscordCreateGuildApplicationCommand 
 * @brief @b POST /applications/{application.id}/guilds/{guild.id}/commands
 *
 * Create a new guild command. New guild commands will be available in 
 * the guild immediately. Returns an application command object. If 
 * the command did not already exist, it will count toward daily 
 * application command create limits.
 * @see https://discord.com/developers/docs/interactions/application-commands#create-guild-application-command
 * @note Creating a command with the same name as an existing command for your application will overwrite the old command.
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the command is located
 * @param params request parameters
 * @param p_app_cmd the application command object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_create_guild_application_command(struct discord *client, const u64_snowflake_t application_id, const u64_snowflake_t guild_id, struct discord_create_guild_application_command_params *params, struct discord_application_command *p_app_cmd);
/// @struct discord_create_guild_application_command_params
/** @} DiscordCreateGuildApplicationCommand */

/** @defgroup DiscordGetGuildApplicationCommand
 * @brief @b GET /applications/{application.id}/guilds/{guild.id}/commands/{command.id}
 *
 * Fetch a guild command for your application. Returns an application command object.
 * @see https://discord.com/developers/docs/interactions/application-commands#get-guild-application-command
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the command is located
 * @param command_id the registered command id
 * @param p_app_cmd the application command object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_get_guild_application_command(struct discord *client, const u64_snowflake_t application_id, const u64_snowflake_t guild_id, const u64_snowflake_t command_id, struct discord_application_command *p_app_cmd);
/** @} DiscordGetGuildApplicationCommand */

/** @defgroup DiscordEditGuildApplicationCommand
 * @brief @b PATCH /applications/{application.id}/guilds/{guild.id}/commands/{command.id}
 *
 * Edit a guild command. Updates for guild commands will be available
 * immediately. Returns an application command object.
 * @see https://discord.com/developers/docs/interactions/application-commands#edit-guild-application-command
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the command is located
 * @param command_id the registered command id
 * @param params request parameters
 * @param p_app_cmd the application command object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_edit_guild_application_command(struct discord *client, const u64_snowflake_t application_id, const u64_snowflake_t guild_id, const u64_snowflake_t command_id, struct discord_edit_guild_application_command_params *params, struct discord_application_command *p_app_cmd);
/// @struct discord_edit_guild_application_command_params
/** @} DiscordEditGuildApplicationCommand */

/** @defgroup DiscordDeleteGuildApplicationCommand
 * @brief @b DELETE /applications/{application.id}/guilds/{guild.id}/commands/{command.id}
 *
 * Deletes a guild command.
 * @see https://discord.com/developers/docs/interactions/application-commands#delete-guild-application-command
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the command is located
 * @param command_id the registered command id
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_delete_guild_application_command(struct discord *client, const u64_snowflake_t application_id, const u64_snowflake_t guild_id, const u64_snowflake_t command_id);
/** @} DiscordDeleteGuildApplicationCommand */

/** @defgroup DiscordBulkOverwriteGuildApplicationCommand
 * @brief @b PUT /applications/{application.id}/guilds/{guild.id}/commands
 *
 * Takes a list of application commands, overwriting existing commands 
 * for the guild. Returns a list of application command objects.
 * @see https://discord.com/developers/docs/interactions/application-commands#bulk-overwrite-guild-application-commands
 * @warning This will overwrite all types of application commands: slash commands, user commands, and message commands.
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the commands are located
 * @param params the request parameters, a list of application commands
 * @param p_app_cmds the null-terminated array of application command objects if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_bulk_overwrite_global_application_command(struct discord *client, const u64_snowflake_t application_id, NTL_T(struct discord_application_command) params, NTL_T(struct discord_application_command) *p_app_cmds);
/** @} DiscordBulkOverwriteGuildApplicationCommand */

/** @defgroup DiscordGetGuildApplicationCommandPermissions
 * @brief @b GET /applications/{application.id}/guilds/{guild.id}/commands/permissions
 *
 * Fetches command permissions for all commands for your application in a guild. Returns an array of guild application command permissions objects.
 * @see https://discord.com/developers/docs/interactions/application-commands#get-guild-application-command-permissions
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the commands are located
 * @param p_permissions the null-terminated array of guild application command permissions objects if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_get_guild_application_command_permissions(struct discord *client, const u64_snowflake_t application_id, const u64_snowflake_t guild_id, NTL_T(struct discord_guild_application_command_permissions) *p_permissions);
/** @} DiscordGetGuildApplicationCommandPermissions */

/** @defgroup DiscordGetApplicationCommandPermissions
 * @brief @b GET /applications/{application.id}/guilds/{guild.id}/commands/{command.id}/permissions
 *
 * Fetches command permissions for a specific command for your application in a guild. Returns a guild application command permissions object.
 * @see https://discord.com/developers/docs/interactions/application-commands#get-application-command-permissions
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the command is located
 * @param command_id the registered command id
 * @param p_permissions the application command permissions object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_get_application_command_permissions(struct discord *client, const u64_snowflake_t application_id, const u64_snowflake_t guild_id, const u64_snowflake_t command_id, struct discord_guild_application_command_permissions *p_permissions);
/** @} DiscordGetApplicationCommandPermissions */

/** @defgroup DiscordEditApplicationCommandPermissions
 * @brief @b PUT /applications/{application.id}/guilds/{guild.id}/commands/{command.id}/permissions
 *
 * Edits command permissions for a specific command for your application in a guild. You can only add up to 10 permission overwrites for a command. Returns a guild application command permissions object.
 * @see https://discord.com/developers/docs/interactions/application-commands#edit-application-command-permissions
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the commands are located
 * @param command_id the registered command id
 * @param params the request parameters
 * @param p_permissions the application command permissions object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_edit_application_command_permissions(struct discord *client, const u64_snowflake_t application_id, const u64_snowflake_t guild_id, const u64_snowflake_t command_id, struct discord_edit_application_command_permissions_params *params, struct discord_guild_application_command_permissions *p_permissions);
/// @struct discord_edit_application_command_permissions_params
/** @} DiscordEditApplicationCommandPermissions */

/** @defgroup DiscordBatchEditApplicationCommandPermissions
 * @brief @b PUT /applications/{application.id}/guilds/{guild.id}/commands/permissions
 *
 * Batch edits permissions for all commands in a guild. Takes an array 
 * of partial guild application command permissions objects including 
 * id and permissions.  
 * You can only add up to 10 permission overwrites for a command.  
 * Returns an array of GuildApplicationCommandPermissions objects.
 * @see https://discord.com/developers/docs/interactions/application-commands#batch-edit-application-command-permissions
 * @warning This will overwrite all types of application commands: slash commands, user commands, and message commands.
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the commands are located
 * @param params the request parameters, a list of guild application commands permissions
 * @param p_permissions the null-terminated array of guild application command permissions objects if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_batch_edit_application_command_permissions(struct discord *client, const u64_snowflake_t application_id, const u64_snowflake_t guild_id, NTL_T(struct discord_guild_application_command_permissions) params, NTL_T(struct discord_guild_application_command_permissions) *p_permissions);
/** @} DiscordBatchEditApplicationCommandPermissions */


/** @defgroup DiscordCreateInteractionResponse
 * @brief @b POST /interactions/{interaction.id}/{interaction.token}/callback
 *
 * Create a response to an Interaction from the gateway. Takes an interaction response.
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#create-interaction-response
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param interaction_id the unique id of the interaction
 * @param interaction_token the unique token of the interaction
 * @param params the request parameters
 * @param p_response the interaction response object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_create_interaction_response(struct discord *client, const u64_snowflake_t interaction_id, const char interaction_token[], struct discord_interaction_response *params, struct discord_interaction_response *p_response);
/** @} DiscordCreateInteractionResponse */

/** @defgroup DiscordGetOriginalInteractionResponse
 * @brief @b GET /webhooks/{interaction.id}/{interaction.token}/messages/@original
 *
 * Returns the initial Interaction response.
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#get-original-interaction-response
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param interaction_id the unique id of the interaction
 * @param interaction_token the unique token of the interaction
 * @param p_response the interaction response object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_get_original_interaction_response(struct discord *client, const u64_snowflake_t interaction_id, const char interaction_token[], struct discord_interaction_response *p_response);
/** @} DiscordGetOriginalInteractionResponse */

/** @defgroup DiscordEditOriginalInteractionResponse
 * @brief @b PATCH /webhooks/{interaction.id}/{interaction.token}/messages/@original
 *
 * Edit the initial Interaction response.
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#edit-original-interaction-response
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param interaction_id the unique id of the interaction
 * @param interaction_token the unique token of the interaction
 * @param params request parameters
 * @param p_response the interaction response object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_edit_original_interaction_response(struct discord *client, const u64_snowflake_t interaction_id, const char interaction_token[], struct discord_edit_original_interaction_response_params *params, struct discord_interaction_response *p_response);
/** @} DiscordEditOriginalInteractionResponse */

/** @defgroup DiscordDeleteOriginalInteractionResponse
 * @brief @b DELETE /webhooks/{interaction.id}/{interaction.token}/messages/@original
 *
 * Delete the initial Interaction response.
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#delete-original-interaction-response
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param interaction_id the unique id of the interaction
 * @param interaction_token the unique token of the interaction
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_delete_original_interaction_response(struct discord *client, const u64_snowflake_t interaction_id, const char interaction_token[]);
/** @} DiscordDeleteOriginalInteractionResponse */

/** @defgroup DiscordCreateFollowupMessage
 * @brief @b POST /webhooks/{interaction.id}/{interaction.token}
 *
 * Create a followup message for an Interaction.
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#create-followup-message
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param application_id the unique id of the application
 * @param interaction_token the unique token of the interaction
 * @param params request parameters
 * @param p_webhook the webhook object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_create_followup_message(struct discord *client, const u64_snowflake_t application_id, const char interaction_token[], struct discord_create_followup_message_params *params, struct discord_webhook *p_webhook);
/// @struct discord_create_followup_message_params
/** @} DiscordCreateFollowupMessage */

/** @defgroup DiscordGetFollowupMessage
 * @brief @b GET /webhooks/{interaction.id}/{interaction.token}/messages/{message.id}
 *
 * Returns a followup message for an interaction.
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#get-followup-message
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param application_id the unique id of the application
 * @param interaction_token the unique token of the interaction
 * @param message_id the unique id of the message
 * @param p_message the message object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_get_followup_message(struct discord *client, const u64_snowflake_t application_id, const char interaction_token[], const u64_snowflake_t message_id, struct discord_message *p_message);
/** @} DiscordGetFollowupMessage */

/** @defgroup DiscordEditFollowupMessage
 * @brief @b PATCH /webhooks/{application.id}/{interaction.token}/messages/{message.id}
 *
 * Edits a followup message for an interaction.
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#edit-followup-message
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param application_id the unique id of the application
 * @param interaction_token the unique token of the interaction
 * @param message_id the unique id of the message
 * @param params request parameters
 * @param p_message the message object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_edit_followup_message(struct discord *client, const u64_snowflake_t application_id, const char interaction_token[], const u64_snowflake_t message_id, struct discord_edit_followup_message_params *params, struct discord_message *p_message);
/// @struct discord_edit_followup_message_params
/** @} DiscordEditFollowupMessage */

/** @defgroup DiscordDeleteFollowupMessage
 * @brief @b DELETE /webhooks/{application.id}/{interaction.token}/messages/{message.id}
 *
 * Edits a followup message for an interaction.
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#edit-followup-message
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param application_id the unique id of the application
 * @param interaction_token the unique token of the interaction
 * @param message_id the unique id of the message
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_delete_followup_message(struct discord *client, const u64_snowflake_t application_id, const char interaction_token[], const u64_snowflake_t message_id);
/** @} DiscordDeleteFollowupMessage */


/** @defgroup DiscordGetGuildAuditLog 
 * @brief @b GET /guilds/{guild.id}/audit-logs
 *
 * Returns an audit log object for the guild. 
 * @see https://discord.com/developers/docs/resources/audit-log#get-guild-audit-log
 * @note Requires the 'VIEW_AUDIT_LOG' permission
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param guild_id the guild to retrieve the audit log from
 * @param params request parameters
 * @param p_audit_log the audit log object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_get_guild_audit_log(struct discord *client, const u64_snowflake_t guild_id, struct discord_get_guild_audit_log_params *params, struct discord_audit_log *p_audit_log);
/// @struct discord_get_guild_audit_log_params
/** @} DiscordGetGuildAuditLog */


/** @defgroup DiscordGetChannel
 * @brief @b GET /channels/{channel.id}
 *
 * Get a channel by ID. Returns a channel object. If the channel is a thread, a thread member object is included in the returned result.
 * @see https://discord.com/developers/docs/resources/channel#get-channel
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param channel_id the channel to be retrieved
 * @param p_channel the channel object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_get_channel(struct discord *client, const u64_snowflake_t channel_id, struct discord_channel *p_channel);
/** @} DiscordGetChannel */

/** @defgroup DiscordModifyChannel
 * @brief @b PATCH /channels/{channel.id}
 *
 * Update a channel's settings.
 * @see https://discord.com/developers/docs/resources/channel#modify-channel
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param channel_id the channel to be modified
 * @param params request parameters
 * @param p_channel the channel object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_modify_channel(struct discord *client, const u64_snowflake_t channel_id, struct discord_modify_channel_params *params, struct discord_channel *p_channel);
/// @struct discord_modify_channel_params
/** @} DiscordModifyChannel */

/** @defgroup DiscordDeleteChannel
 * @brief @b DELETE /channels/{channel.id}
 *
 * Delete a channel, or close a private message.
 * @note Requires the MANAGE_CHANNELS permission for the guild, or MANAGE_THREADS if the channel is a thread. Deleting a category does not delete its child channels; they will have their parent_id removed and a Channel Update Gateway event will fire for each of them.
 * @note Fires a Channel Delete Gateway event (or Thread Delete if the channel was a thread).
 * @see https://discord.com/developers/docs/resources/channel#deleteclose-channel
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param channel_id the channel to be deleted
 * @param p_channel the channel object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_delete_channel(struct discord *client, const u64_snowflake_t channel_id, struct discord_channel *p_channel);
/** @} DiscordDeleteChannel */

/** @defgroup DiscordGetChannelMessages
 * @brief @b GET /channels/{channel.id}/messages
 *
 * Returns the messages for a channel.
 * @note If operating on a guild channel, this endpoint requires the VIEW_CHANNEL permission to be present on the current user.
 * @note If the current user is missing the 'READ_MESSAGE_HISTORY' permission in the channel then this will return no messages (since they cannot read the message history).
 * @note The before, after, and around keys are mutually exclusive, only one may be passed at a time.
 * @see https://discord.com/developers/docs/resources/channel#get-channel-messages
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param channel_id the channel to get messages from
 * @param params request parameters
 * @param p_messages the null-terminated array of messages if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_get_channel_messages(struct discord *client, const u64_snowflake_t channel_id, struct discord_get_channel_messages_params *params, NTL_T(struct discord_message) *p_messages);
/// @struct discord_get_channel_messages_params
/** @} DiscordGetChannelMessages */

/** @defgroup DiscordGetChannelMessage
 * @brief @b GET /channels/{channel.id}/messages/{message.id}
 *
 * Returns a specific message in the channel.
 * @note If operating on a guild channel, this endpoint requires the 'READ_MESSAGE_HISTORY' permission to be present on the current user.
 * @see https://discord.com/developers/docs/resources/channel#get-channel-message
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param channel_id the channel where the message resides
 * @param message_id the message itself
 * @param p_message the message object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_get_channel_message(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, struct discord_message *p_message);
/** @} DiscordGetChannelMessage */

/** @defgroup DiscordCreateMessage
 * @brief @b POST /channels/{channel.id}/messages
 *
 * Post a message to a guild text or DM channel. Fires a Message Create Gateway event.
 * @see https://discord.com/developers/docs/resources/channel#create-message
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param channel_id the channel to send the message at
 * @param params request parameters
 * @param p_message the message object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_create_message(struct discord *client, const u64_snowflake_t channel_id, struct discord_create_message_params *params, struct discord_message *p_message);
/// @struct discord_create_message_params
/** @} DiscordCreateMessage */

/** @defgroup DiscordCrosspostMessage
 * @brief @b POST /channels/{channel.id}/messages/{message.id}/crosspost
 *
 * Crosspost a message in a News Channel to following channels. This endpoint requires the 'SEND_MESSAGES' permission, if the current user sent the message, or additionally the 'MANAGE_MESSAGES' permission, for all other messages, to be present for the current user.
 * @see https://discord.com/developers/docs/resources/channel#crosspost-message
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param channel_id the news channel that will crosspost
 * @param message_id the message that will crospost
 * @param p_message the message object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_crosspost_message(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, struct discord_message *p_message);
/** @} DiscordCrosspostMessage */

/** @defgroup DiscordCreateReaction
 * @brief @b PUT /channels/{channel.id}/messages/{message.id}/reactions/{emoji}/@@me
 *
 * Create a reaction for the message.
 * @see https://discord.com/developers/docs/resources/channel#create-reaction
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message to receive a reaction
 * @param emoji_id the emoji id (leave as 0 if not a custom emoji)
 * @param emoji_name the emoji name
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_create_reaction(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, const u64_snowflake_t emoji_id, const char emoji_name[]);
/** @} DiscordCreateReaction */

/** @defgroup DiscordDeleteOwnReaction
 * @brief @b DELETE /channels/{channel.id}/messages/{message.id}/reactions/{emoji}/@@me
 *
 * Delete a reaction the current user has made for the message.
 * @see https://discord.com/developers/docs/resources/channel#delete-own-reaction
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message to have a reaction deleted
 * @param emoji_id the emoji id (leave as 0 if not a custom emoji)
 * @param emoji_name the emoji name
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_delete_own_reaction(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, const u64_snowflake_t emoji_id, const char emoji_name[]);
/** @} DiscordDeleteOwnReaction */

/** @defgroup DiscordDeleteUserReaction
 * @brief @b DELETE /channels/{channel.id}/messages/{message.id}/reactions/{emoji}/{user.id}
 *
 * Deletes another user's reaction.
 * @see https://discord.com/developers/docs/resources/channel#delete-user-reaction
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message to have a reaction deleted
 * @param user_id the user the reaction belongs to
 * @param emoji_id the emoji id (leave as 0 if not a custom emoji)
 * @param emoji_name the emoji name
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_delete_user_reaction(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, const u64_snowflake_t user_id, const u64_snowflake_t emoji_id, const char emoji_name[]);
/** @} DiscordDeleteUserReaction */

/** @defgroup DiscordGetReactions
 * @brief @b GET /channels/{channel.id}/messages/{message.id}/reactions/{emoji}
 *
 * Get a list of users that reacted with this emoji.
 * @see https://discord.com/developers/docs/resources/channel#get-reactions
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message reacted to
 * @param emoji_id the emoji id (leave as 0 if not a custom emoji)
 * @param emoji_name the emoji name
 * @param params request parameters
 * @param p_users the null-terminated array of users if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_get_reactions(struct discord *client, u64_snowflake_t channel_id, u64_snowflake_t message_id, const u64_snowflake_t emoji_id, const char emoji_name[], struct discord_get_reactions_params *params, NTL_T(struct discord_user) *p_users);
/// @struct discord_get_reactions_params
/** @} DiscordGetReactions */

/** @defgroup DiscordDeleteAllReactions
 * @brief @b DELETE /channels/{channel.id}/messages/{message.id}/reactions
 *
 * Deletes all reactions on a message.
 * @see https://discord.com/developers/docs/resources/channel#delete-all-reactions
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message that will be purged of reactions
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_delete_all_reactions(struct discord *client, u64_snowflake_t channel_id, u64_snowflake_t message_id);
/** @} DiscordDeleteAllReactions */

/** @defgroup DiscordDeleteAllReactionsForEmoji
 * @brief @b DELETE /channels/{channel.id}/messages/{message.id}/reactions/{emoji}
 *
 * Deletes all the reactions for a given emoji on a message.
 * @see https://discord.com/developers/docs/resources/channel#delete-all-reactions-for-emoji
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message that will be purged of reactions from particular emoji
 * @param emoji_id the emoji id (leave as 0 if not a custom emoji)
 * @param emoji_name the emoji name
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 */
ORCAcode discord_delete_all_reactions_for_emoji(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, const u64_snowflake_t emoji_id, const char emoji_name[]);
/** @} DiscordDeleteAllReactionsForEmoji */

/** @defgroup DiscordEditMessage
 *  @{ */
ORCAcode discord_edit_message(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, struct discord_edit_message_params *params, struct discord_message *p_message);
/// @struct discord_edit_message_params
/** @} DiscordEditMessage */

/** @defgroup DiscordDeleteMessage
 *  @{ */
ORCAcode discord_delete_message(struct discord *client, u64_snowflake_t channel_id, u64_snowflake_t message_id);
/** @} DiscordDeleteMessage */

/** @defgroup DiscordBulkDeleteMessages
 *  @{ */
ORCAcode discord_bulk_delete_messages(struct discord *client, u64_snowflake_t channel_id, NTL_T(u64_snowflake_t) messages);
/** @} DiscordBulkDeleteMessages */

/** @defgroup DiscordEditChannelPermissions
 *  @{ */
ORCAcode discord_edit_channel_permissions(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t overwrite_id, struct discord_edit_channel_permissions_params *params);
/// @struct discord_edit_channel_permissions_params
/** @} DiscordEditChannelPermissions */

/** @defgroup DiscordGetChannelInvites
 *  @{ */
ORCAcode discord_get_channel_invites(struct discord *client, const u64_snowflake_t channel_id, NTL_T(struct discord_invite) *p_invites);
/** @} DiscordGetChannelInvites */

/** @defgroup DiscordCreateChannelInvite
 *  @{ */
ORCAcode discord_create_channel_invite(struct discord *client, const u64_snowflake_t channel_id, struct discord_create_channel_invite_params *params, struct discord_invite *p_invite);
/// @struct discord_create_channel_invite_params
/** @} DiscordCreateChannelInvite */

/** @defgroup DiscordDeleteChannelPermission
 *  @{ */
ORCAcode discord_delete_channel_permission(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t overwrite_id);
/** @} DiscordDeleteChannelPermission */

/** @defgroup DiscordTriggerTypingIndicator
 *  @{ */
ORCAcode discord_trigger_typing_indicator(struct discord* client, u64_snowflake_t channel_id);
/** @} DiscordTriggerTypingIndicator */

/** @defgroup DiscordFollowNewsChannel
 *  @{ */
ORCAcode discord_follow_news_channel(struct discord *client, const u64_snowflake_t channel_id, struct discord_follow_news_channel_params *params, struct discord_channel *p_followed_channel);
/// @struct discord_follow_news_channel_params
/** @} DiscordFollowNewsChannel */

/** @defgroup DiscordGetPinnedMessages
 *  @{ */
ORCAcode discord_get_pinned_messages(struct discord *client, const u64_snowflake_t channel_id, NTL_T(struct discord_message) *p_messages);
/** @} DiscordGetPinnedMessages */

/** @defgroup DiscordPinMessage
 *  @{ */
ORCAcode discord_pin_message(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id);
/** @} DiscordPinMessage */

/** @defgroup DiscordUnpinMessage
 *  @{ */
ORCAcode discord_unpin_message(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id);
/** @} DiscordUnpinMessage */

/** @defgroup DiscordGroupDmAddRecipient
 *  @{ */
ORCAcode discord_group_dm_add_recipient(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t user_id, struct discord_group_dm_add_recipient_params *params);
/// @struct discord_group_dm_add_recipient_params
/** @} DiscordGroupDmAddRecipient */

/** @defgroup DiscordGroupDmRemoveRecipient
 *  @{ */
ORCAcode discord_group_dm_remove_recipient(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t user_id);
/** @} DiscordGroupDmRemoveRecipient */

/** @defgroup DiscordStartThreadWithMessage
 *  @{ */
ORCAcode discord_start_thread_with_message(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t message_id, struct discord_start_thread_with_message_params *params, struct discord_channel *p_channel);
/// @struct discord_start_thread_with_message_params
/** @} DiscordStartThreadWithMessage */

/** @defgroup DiscordStartThreadWithoutMessage
 *  @{ */
ORCAcode discord_start_thread_without_message(struct discord *client, const u64_snowflake_t channel_id, struct discord_start_thread_without_message_params *params, struct discord_channel *p_channel);
/// @struct discord_start_thread_without_message_params
/** @} DiscordStartThreadWithoutMessage */

/** @defgroup DiscordJoinThread
 *  @{ */
ORCAcode discord_join_thread(struct discord *client, const u64_snowflake_t channel_id);
/** @} DiscordJoinThread */

/** @defgroup DiscordAddThreadMember
 *  @{ */
ORCAcode discord_add_thread_member(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t user_id);
/** @} DiscordAddThreadMember */

/** @defgroup DiscordLeaveThread
 *  @{ */
ORCAcode discord_leave_thread(struct discord *client, const u64_snowflake_t channel_id);
/** @} DiscordLeaveThread */

/** @defgroup DiscordRemoveThreadMember
 *  @{ */
ORCAcode discord_remove_thread_member(struct discord *client, const u64_snowflake_t channel_id, const u64_snowflake_t user_id);
/** @} DiscordRemoveThreadMember */

/** @defgroup DiscordListThreadMembers
 *  @{ */
ORCAcode discord_list_thread_members(struct discord *client, const u64_snowflake_t channel_id, NTL_T(struct discord_thread_member) *p_thread_members);
/** @} DiscordListThreadMembers */

/** @defgroup DiscordListActiveThreads
 *  @{ */
ORCAcode discord_list_active_threads(struct discord *client, const u64_snowflake_t channel_id, struct discord_thread_response_body *body);
/** @} DiscordListActiveThreads */

/** @defgroup DiscordListPublicArchivedThreads
 *  @{ */
ORCAcode discord_list_public_archived_threads(struct discord *client, const u64_snowflake_t channel_id, const u64_unix_ms_t before, const int limit, struct discord_thread_response_body *body);
/** @} DiscordListPublicArchivedThreads */

/** @defgroup DiscordListPrivateArchivedThreads
 *  @{ */
ORCAcode discord_list_private_archived_threads(struct discord *client, const u64_snowflake_t channel_id, const u64_unix_ms_t before, const int limit, struct discord_thread_response_body *body);
/** @} DiscordListPrivateArchivedThreads */

/** @defgroup DiscordListJoinedPrivateArchivedThreads
 *  @{ */
ORCAcode discord_list_joined_private_archived_threads(struct discord *client, const u64_snowflake_t channel_id, const u64_unix_ms_t before, const int limit, struct discord_thread_response_body *body);
/** @} DiscordListJoinedPrivateArchivedThreads */


/** @defgroup DiscordListGuildEmojis
 *  @{ */
ORCAcode discord_list_guild_emojis(struct discord *client, const u64_snowflake_t guild_id, NTL_T(struct discord_emoji) *p_emojis);
/** @} DiscordListGuildEmojis */

/** @defgroup DiscordGetGuildEmoji
 *  @{ */
ORCAcode discord_get_guild_emoji(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t emoji_id, struct discord_emoji *p_emoji);
/** @} DiscordGetGuildEmoji */

/** @defgroup DiscordCreateGuildEmoji
 *  @{ */
ORCAcode discord_create_guild_emoji(struct discord *client, const u64_snowflake_t guild_id, struct discord_create_guild_emoji_params *params, struct discord_emoji *p_emoji);
/// @struct discord_create_guild_emoji_params
/** @} DiscordCreateGuildEmoji */

/** @defgroup DiscordModifyGuildEmoji
 *  @{ */
ORCAcode discord_modify_guild_emoji(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t emoji_id, struct discord_modify_guild_emoji_params *params, struct discord_emoji *p_emoji);
/// @struct discord_modify_guild_emoji_params
/** @} DiscordModifyGuildEmoji */

/** @defgroup DiscordDeleteGuildEmoji
 *  @{ */
ORCAcode discord_delete_guild_emoji(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t emoji_id);
/** @} DiscordDeleteGuildEmoji */


/** @defgroup DiscordCreateGuild
 *  @{ */
ORCAcode discord_create_guild(struct discord *client, struct discord_create_guild_params *params, struct discord_guild *p_guild);
/// @struct discord_create_guild_params
/** @} DiscordCreateGuild */

/** @defgroup DiscordGetGuild
 *  @{ */
ORCAcode discord_get_guild(struct discord *client, const u64_snowflake_t guild_id, struct discord_guild *p_guild);
/** @} DiscordGetGuild */

/** @defgroup DiscordGetGuildPreview
 *  @{ */
ORCAcode discord_get_guild_preview(struct discord *client, const u64_snowflake_t guild_id, struct discord_guild_preview *p_guild_preview);
/** @} DiscordGetGuildPreview */

/** @defgroup DiscordModifyGuild
 *  @{ */
ORCAcode discord_modify_guild(struct discord *client, const u64_snowflake_t guild_id, struct discord_modify_guild_params *params, struct discord_guild *p_guild);
/// @struct discord_modify_guild_params
/** @} DiscordModifyGuild */

/** @defgroup DiscordDeleteGuild
 *  @{ */
ORCAcode discord_delete_guild(struct discord *client, const u64_snowflake_t guild_id);
/** @} DiscordDeleteGuild */

/** @defgroup DiscordGetGuildChannels
 *  @{ */
ORCAcode discord_get_guild_channels(struct discord *client, const u64_snowflake_t guild_id, NTL_T(struct discord_channel) *p_channels);
/** @} DiscordGetGuildChannels */

/** @defgroup DiscordCreateGuildChannel
 *  @{ */
ORCAcode discord_create_guild_channel(struct discord *client, const u64_snowflake_t guild_id, struct discord_create_guild_channel_params *params, struct discord_channel *p_channel);
/// @struct discord_create_guild_channel_params
/** @} DiscordCreateGuildChannel */

/** @defgroup DiscordModifyGuildChannelPositions
 *  @{ */
ORCAcode discord_modify_guild_channel_positions(struct discord *client, const u64_snowflake_t guild_id, NTL_T(struct discord_modify_guild_channel_positions_params) params);
/// @struct discord_modify_guild_channel_positions_params
/** @} DiscordModifyGuildChannelPositions */

/** @defgroup DiscordGetGuildMember
 *  @{ */
ORCAcode  discord_get_guild_member(struct discord *client, u64_snowflake_t guild_id, u64_snowflake_t user_id, struct discord_guild_member *p_member);
/** @} DiscordGetGuildMember */

/** @defgroup DiscordListGuildMembers
 *  @{ */
ORCAcode discord_list_guild_members(struct discord *client, const u64_snowflake_t guild_id, struct discord_list_guild_members_params *params, NTL_T(struct discord_guild_member) *p_members);
/// @struct discord_list_guild_members_params
/** @} DiscordListGuildMembers */

/** @defgroup DiscordSearchGuildMembers
 *  @{ */
ORCAcode discord_search_guild_members(struct discord *client, const u64_snowflake_t guild_id, struct discord_search_guild_members_params *params, NTL_T(struct discord_guild_member) *p_members);
/// @struct discord_search_guild_members_params
/** @} DiscordSearchGuildMembers */

/** @defgroup DiscordModifyGuildMember
 *  @{ */
ORCAcode discord_modify_guild_member(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, struct discord_modify_guild_member_params *params, struct discord_guild_member *p_member);
/// @struct discord_modify_guild_member_params
/** @} DiscordModifyGuildMember */

/** @defgroup DiscordAddGuildMember
 *  @{ */
ORCAcode discord_add_guild_member(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, struct discord_add_guild_member_params *params, struct discord_guild_member *p_member);
/// @struct discord_add_guild_member_params
/** @} DiscordAddGuildMember */

/** @defgroup DiscordModifyCurrentUserNick
 *  @{ */
ORCAcode discord_modify_current_user_nick(struct discord *client, const u64_snowflake_t guild_id, const char nick[]);
/** @} DiscordModifyCurrentUserNick */

/** @defgroup DiscordAddGuildMemberRole
 *  @{ */
ORCAcode discord_add_guild_member_role(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, const u64_snowflake_t role_id);
/** @} DiscordAddGuildMemberRole */

/** @defgroup DiscordRemoveGuildMemberRole
 *  @{ */
ORCAcode discord_remove_guild_member_role(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, const u64_snowflake_t role_id);
/** @} DiscordRemoveGuildMemberRole */

/** @defgroup DiscordRemoveGuildMember
 *  @{ */
ORCAcode discord_remove_guild_member(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id);
/** @} DiscordRemoveGuildMember */

/** @defgroup DiscordGetGuildBans
 *  @{ */
ORCAcode discord_get_guild_bans(struct discord *client, const u64_snowflake_t guild_id, NTL_T(struct discord_ban) *p_bans);
/** @} DiscordGetGuildBans */

/** @defgroup DiscordGetGuildBan
 *  @{ */
ORCAcode discord_get_guild_ban(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, struct discord_ban *p_ban);
/** @} DiscordGetGuildBan */

/** @defgroup DiscordCreateGuildBan
 *  @{ */
ORCAcode discord_create_guild_ban(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, int delete_message_days, const char reason[]);
/** @} DiscordCreateGuildBan */

/** @defgroup DiscordRemoveGuildBan
 *  @{ */
ORCAcode discord_remove_guild_ban(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, const char reason[]);
/** @} DiscordRemoveGuildBan */

/** @defgroup DiscordGetGuildRoles
 *  @{ */
ORCAcode discord_get_guild_roles(struct discord *client, const u64_snowflake_t guild_id, NTL_T(struct discord_role) *p_roles);
/** @} DiscordGetGuildRoles */

/** @defgroup DiscordCreateGuildRole
 *  @{ */
ORCAcode discord_create_guild_role(struct discord *client, const u64_snowflake_t guild_id, struct discord_create_guild_role_params *params, struct discord_role *p_role);
/// @struct discord_create_guild_role_params
/** @} DiscordCreateGuildRole */

/** @defgroup DiscordModifyGuildRolePositions
 *  @{ */
ORCAcode discord_modify_guild_role_positions(struct discord *client, const u64_snowflake_t guild_id, NTL_T(struct discord_modify_guild_role_positions_params) params, NTL_T(struct discord_role) *p_roles);
/// @struct discord_modify_guild_role_positions_params
/** @} DiscordModifyGuildRolePositions */

/** @defgroup DiscordModifyGuildRole
 *  @{ */
ORCAcode discord_modify_guild_role(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t role_id, struct discord_modify_guild_role_params *params, struct discord_role *p_role);
/// @struct discord_modify_guild_role_params
/** @} DiscordModifyGuildRole */

/** @defgroup DiscordDeleteGuildRole
 *  @{ */
ORCAcode discord_delete_guild_role(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t role_id);
/** @} DiscordDeleteGuildRole */


/** @defgroup DiscordGetInvite
 *  @{ */
ORCAcode discord_get_invite(struct discord *client, char *invite_code, struct discord_get_invite_params *params, struct discord_invite *p_invite);
/// @struct discord_get_invite_params
/** @} DiscordGetInvite */

/** @defgroup DiscordDeleteInvite
 *  @{ */
ORCAcode discord_delete_invite(struct discord *client, char *invite_code, struct discord_invite *p_invite);
/** @} DiscordDeleteInvite */


/** @defgroup DiscordGetUser
 *  @{ */
ORCAcode discord_get_user(struct discord *client, const u64_snowflake_t user_id, struct discord_user *p_user);
/** @} DiscordGetUser */

/** @defgroup DiscordModifyCurrentUser
 *  @{ */
ORCAcode discord_modify_current_user(struct discord *client, struct discord_modify_current_user_params *params, struct discord_user *p_user);
/// @struct discord_modify_current_user_params
/** @} DiscordModifyCurrentUser */

/** @defgroup DiscordGetCurrentUser
 *  @{ */
ORCAcode discord_get_current_user(struct discord *client, struct discord_user *p_user);
ORCAcode sb_discord_get_current_user(struct discord *client, struct sized_buffer *p_sb_user);
/** @} DiscordGetCurrentUser */

/** @defgroup DiscordGetCurrentUserGuilds
 *  @{ */
ORCAcode discord_get_current_user_guilds(struct discord *client, NTL_T(struct discord_guild) *p_guilds);
/** @} DiscordGetCurrentUserGuilds */

/** @defgroup DiscordLeaveGuild
 *  @{ */
ORCAcode discord_leave_guild(struct discord *client, const u64_snowflake_t guild_id);
/** @} DiscordLeaveGuild */

/** @defgroup DiscordCreateDm
 *  @{ */
ORCAcode discord_create_dm(struct discord *client, const u64_snowflake_t recipient_id, struct discord_channel *p_dm_channel);
/** @} DiscordCreateDm */

/** @defgroup DiscordCreateGroupDm
 *  @{ */
ORCAcode discord_create_group_dm(struct discord *client, struct discord_create_group_dm_params *params, struct discord_channel *p_dm_channel);
/// @struct discord_create_group_dm_params
/** @} DiscordCreateGroupDm */

/** @defgroup DiscordGetUserConnections
 *  @{ */
ORCAcode discord_get_user_connections(struct discord *client, NTL_T(struct discord_connection) *p_connections);
/** @} DiscordGetUserConnections */


/** @defgroup DiscordListVoiceRegions
 *  @{ */
ORCAcode discord_list_voice_regions(struct discord *client, NTL_T(struct discord_voice_region) *p_voice_regions);
/** @} DiscordListVoiceRegions */


/** @defgroup DiscordCreateWebhook
 * @brief @b POST /channels/{channel.id}/webhooks
 *
 * Create a new webhook. Requires the MANAGE_WEBHOOKS permission. Returns a webhook object on success.
 * @see https://discord.com/developers/docs/resources/webhook#create-webhook
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param channel_id the channel that the webhook belongs to
 * @param params request parameters
 * @param p_webhook the webhook object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 *  @{ */
ORCAcode discord_create_webhook(struct discord *client, const u64_snowflake_t channel_id, struct discord_create_webhook_params *params, struct discord_webhook *p_webhook);
/// @struct discord_create_webhook_params
/** @} DiscordCreateWebhook */

/** @defgroup DiscordGetChannelWebhooks
 * @brief @b GET /channels/{channel.id}/webhooks
 *
 * Returns a list of channel webhook objects. Requires the MANAGE_WEBHOOKS permission.
 * @see https://discord.com/developers/docs/resources/webhook#get-channel-webhooks
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param channel_id the channel that the webhooks belongs to
 * @param p_webhooks a null-terminated list of webhook objects if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 *  @{ */
ORCAcode discord_get_channel_webhooks(struct discord *client, const u64_snowflake_t channel_id, NTL_T(struct discord_webhook) *p_webhooks);
/** @} DiscordGetChannelWebhooks */

/** @defgroup DiscordGetGuildWebhooks
 * @brief @b GET /guilds/{guild.id}/webhooks
 *
 * Returns a list of guild webhook objects. Requires the MANAGE_WEBHOOKS permission.
 * @see https://discord.com/developers/docs/resources/webhook#get-guild-webhooks
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param guild_id the guild that the webhooks belongs to
 * @param p_webhooks a null-terminated list of webhook objects if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 *  @{ */
ORCAcode discord_get_guild_webhooks(struct discord *client, const u64_snowflake_t guild_id, NTL_T(struct discord_webhook) *p_webhooks);
/** @} DiscordGetGuildWebhooks */

/** @defgroup DiscordGetWebhook
 * @brief @b GET /webhooks/{webhook.id}
 *
 * Returns the new webhook object for the given id.
 * @see https://discord.com/developers/docs/resources/webhook#get-webhook
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param p_webhook the webhook object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 *  @{ */
ORCAcode discord_get_webhook(struct discord *client, const u64_snowflake_t webhook_id, struct discord_webhook *p_webhook);
/** @} DiscordGetWebhook */

/** @defgroup DiscordGetWebhookWithToken
 * @brief @b GET /webhooks/{webhook.id}/{webhook.token}
 *
 * Same discord_get_webhook(), except this call does not require authentication and returns no user in the webhook object
 * @see https://discord.com/developers/docs/resources/webhook#get-webhook-with-token
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @param p_webhook the webhook object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 *  @{ */
ORCAcode discord_get_webhook_with_token(struct discord *client, const u64_snowflake_t webhook_id, const char webhook_token[], struct discord_webhook *p_webhook);
/** @} DiscordGetWebhookWithToken */

/** @defgroup DiscordModifyWebhook
 * @brief @b PATCH /webhooks/{webhook.id}
 *
 * Modify a webhook. Requires the MANAGE_WEBHOOKS permission. Returns the updated webhook object on success.
 * @see https://discord.com/developers/docs/resources/webhook#modify-webhook
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param params request parameters
 * @param p_webhook the webhook object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 *  @{ */
ORCAcode discord_modify_webhook(struct discord *client, const u64_snowflake_t webhook_id, struct discord_modify_webhook_params *params, struct discord_webhook *p_webhook);
/// @struct discord_modify_webhook_params
/** @} DiscordModifyWebhook */

/** @defgroup DiscordModifyWebhookWithToken
 * @brief @b PATCH /webhooks/{webhook.id}/{webhook.token}
 *
 * Same discord_modify_webhook(), except this call does not require authentication and returns no user in the webhook object
 * @see https://discord.com/developers/docs/resources/webhook#modify-webhook-with-token
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @param params request parameters
 * @param p_webhook the webhook object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 *  @{ */
ORCAcode discord_modify_webhook_with_token(struct discord *client, const u64_snowflake_t webhook_id, const char webhook_token[], struct discord_modify_webhook_with_token_params *params, struct discord_webhook *p_webhook);
/// @struct discord_modify_webhook_with_token_params
/** @} DiscordModifyWebhookWithToken */

/** @defgroup DiscordDeleteWebhook
 * @brief @b DELETE /webhooks/{webhook.id}
 *
 * Delete a webhook permanently. Requires the MANAGE_WEBHOOKS permission.
 * @see https://discord.com/developers/docs/resources/webhook#delete-webhook
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 *  @{ */
ORCAcode discord_delete_webhook(struct discord *client, const u64_snowflake_t webhook_id);
/** @} DiscordDeleteWebhook */

/** @defgroup DiscordDeleteWebhookWithToken
 * @brief @b DELETE /webhooks/{webhook.id}/{webhook.token}
 *
 * Same discord_delete_webhook(), except this call does not require authentication.
 * @see https://discord.com/developers/docs/resources/webhook#delete-webhook-with-token
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 *  @{ */
ORCAcode discord_delete_webhook_with_token(struct discord *client, const u64_snowflake_t webhook_id, const char webhook_token[]);
/** @} DiscordDeleteWebhookWithToken */

/** @defgroup DiscordExecuteWebhook
 * @brief @b POST /webhooks/{webhook.id}/{webhook.token}
 *
 * @see https://discord.com/developers/docs/resources/webhook#execute-webhook
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @param params request parameters
 * @param p_webhook the webhook object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 *  @{ */
ORCAcode discord_execute_webhook(struct discord *client, const u64_snowflake_t webhook_id, const char webhook_token[], struct discord_execute_webhook_params *params, struct discord_webhook *p_webhook);
/// @struct discord_execute_webhook_params
/** @} DiscordExecuteWebhook */

/** @defgroup DiscordGetWebhookMessage
 * @brief @b GET /webhooks/{webhook.id}/{webhook.token}/messages/{message.id}
 *
 * Returns a previously-sent webhook message from the same token. Returns a message object on success.
 * @see https://discord.com/developers/docs/resources/webhook#get-webhook-message
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @param message_id the message the webhook belongs to
 * @param p_message the message object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 *  @{ */
ORCAcode discord_get_webhook_message(struct discord *client, const u64_snowflake_t webhook_id, const char webhook_token[], const u64_snowflake_t message_id, struct discord_message *p_message);
/** @} DiscordGetWebhookMessage */

/** @defgroup DiscordEditWebhookMessage
 * @brief @b PATCH /webhooks/{webhook.id}/{webhook.token}/messages/{message.id}
 *
 * Edits a previously-sent webhook message from the same token. Returns a message object on success.
 * @see https://discord.com/developers/docs/resources/webhook#edit-webhook-message
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @param message_id the message the webhook belongs to
 * @param params request parameters
 * @param p_message the message object if succesful
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 *  @{ */
ORCAcode discord_edit_webhook_message(struct discord *client, const u64_snowflake_t webhook_id, const char webhook_token[], const u64_snowflake_t message_id, struct discord_edit_webhook_message_params *params, struct discord_message *p_message);
/// @struct discord_edit_webhook_message_params
/** @} DiscordEditWebhookMessage */

/** @defgroup DiscordDeleteWebhookMessage
 * @brief @b DELETE /webhooks/{webhook.id}/{webhook.token}/messages/{message.id}
 *
 * Deletes a message that was created by the webhook. Returns a 204 NO CONTENT response on success.
 * @see https://discord.com/developers/docs/resources/webhook#delete-webhook-message
 *  @{ */
/**
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @param message_id the message the webhook belongs to
 * @return ORCAcode for how the transfer went, ORCA_OK means a succesful request
 *  @{ */
ORCAcode discord_delete_webhook_message(struct discord *client, const u64_snowflake_t webhook_id, const char webhook_token[], const u64_snowflake_t message_id);
/** @} DiscordDeleteWebhookMessage */


/** @defgroup DiscordGetGateway
 *  @{ */
ORCAcode discord_get_gateway(struct discord *client, struct sized_buffer *p_json);
/** @} DiscordGetGateway */

/** @defgroup DiscordGetGatewayBot
 *  @{ */
ORCAcode discord_get_gateway_bot(struct discord *client, struct sized_buffer *p_json);
/** @} DiscordGetGatewayBot */


/* * * * * * * * * * * * * * * * * * * */
/* * * * MISCELLANEOUS FUNCTIONS * * * */

/** @defgroup DiscordMiscEmbed
 *  @{ */
void discord_embed_set_thumbnail(struct discord_embed *embed, char url[], char proxy_url[], int height, int width);
void discord_embed_set_image(struct discord_embed *embed, char url[], char proxy_url[], int height, int width);
void discord_embed_set_video(struct discord_embed *embed, char url[], char proxy_url[], int height, int width);
void discord_embed_set_footer(struct discord_embed *embed, char text[], char icon_url[], char proxy_icon_url[]);
void discord_embed_set_provider(struct discord_embed *embed, char name[], char url[]);
void discord_embed_set_author(struct discord_embed *embed, char name[], char url[], char icon_url[], char proxy_icon_url[]);
void discord_embed_set_title(struct discord_embed *embed, char format[], ...);
void discord_embed_add_field(struct discord_embed *embed, char name[], char value[], bool Inline);
/** @} DiscordMiscEmbed */

/** @defgroup DiscordMiscChannel
 *  @{ */
void discord_overwrite_append(NTL_T(struct discord_overwrite) *permission_overwrites, u64_snowflake_t id, int type, enum discord_bitwise_permission_flags allow, enum discord_bitwise_permission_flags deny);
ORCAcode discord_get_channel_at_pos(struct discord *client, const u64_snowflake_t guild_id, const enum discord_channel_types type, const size_t position, struct discord_channel *p_channel);
ORCAcode discord_delete_messages_by_author_id(struct discord *client, u64_snowflake_t channel_id, u64_snowflake_t author_id);
/** @} DiscordMiscChannel */

/** @defgroup DiscordMiscGuild
 *  @{ */
ORCAcode discord_disconnect_guild_member(struct discord *client, const u64_snowflake_t guild_id, const u64_snowflake_t user_id, struct discord_guild_member *p_member);
/** @} DiscordMiscGuild */

/** @defgroup DiscordMiscGateway
 *  @{ */
/**
 * @brief Helper function to add presence activities
 *
 * This function is a wrapper over ntl_append2()
 * @see discord_set_presence()
 */
void discord_presence_add_activity(struct discord_presence_status *presence, struct discord_activity *activity);
/** @} DiscordMiscGateway */

#endif // DISCORD_H
