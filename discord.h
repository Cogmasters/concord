/**
 * @file discord.h
 * @author cee-studio
 * @brief File containing public functions and datatypes
 *
 * These symbols are organized in a intuitive fashion to be easily
 *        matched to the official Discord API docs.
 * @see https://discord.com/developers/docs/intro
 */

#ifndef DISCORD_H
#define DISCORD_H

#include <stdbool.h>
#include "json-actor-boxed.h"
#include "common.h"
#include "logconf.h"

/* see specs/discord/ for specs */
#include "specs-code/discord/one-specs.h"

#define DISCORD_API_BASE_URL                 "https://discord.com/api/v9"
#define DISCORD_GATEWAY_URL_SUFFIX           "?v=9&encoding=json"
#define DISCORD_VOICE_CONNECTIONS_URL_SUFFIX "?v=4"

/* forward declarations */
struct discord;
struct discord_voice_cbs;
/**/

/** @defgroup DiscordLimitsSnowflake
 *  @{ */
#define DISCORD_SNOWFLAKE_INCREMENT          12
#define DISCORD_SNOWFLAKE_PROCESS_ID         17
#define DISCORD_SNOWFLAKE_INTERNAL_WORKER_ID 22
#define DISCORD_SNOWFLAKE_TIMESTAMP          64
/** @} */

/** @defgroup DiscordLimitsGeneral
 * @note assume the worst-case scenario for strings, where each character is 4
 *        bytes long (UTF8)
 *  @{ */
#define DISCORD_MAX_NAME_LEN          4 * 100 + 1
#define DISCORD_MAX_TOPIC_LEN         4 * 1024 + 1
#define DISCORD_MAX_DESCRIPTION_LEN   4 * 2048 + 1
#define DISCORD_MAX_USERNAME_LEN      4 * 32 + 1
#define DISCORD_MAX_DISCRIMINATOR_LEN 4 + 1
#define DISCORD_MAX_REASON_LEN        4 * 512 + 1
#define DISCORD_MAX_MESSAGE_LEN       4 * 2000 + 1
#define DISCORD_MAX_PAYLOAD_LEN       4 * 4096 + 1
#define DISCORD_MAX_VOICE_CONNECTIONS 512
/** @} */

/** @defgroup DiscordLimitsEmbed
 * @note assume the worst-case scenario for strings, where each character is 4
 *        bytes long (UTF8)
 *  @{ */
#define DISCORD_EMBED_TITLE_LEN       4 * 256 + 1
#define DISCORD_EMBED_DESCRIPTION_LEN 4 * 2048 + 1
#define DISCORD_EMBED_MAX_FIELDS      25
#define DISCORD_EMBED_FIELD_NAME_LEN  4 * 256 + 1
#define DISCORD_EMBED_FIELD_VALUE_LEN 4 * 1024 + 1
#define DISCORD_EMBED_FOOTER_TEXT_LEN 4 * 2048 + 1
#define DISCORD_EMBED_AUTHOR_NAME_LEN 4 * 256 + 1
/** @} */

/** @defgroup DiscordLimitsWebhook
 * @note assume the worst-case scenario for strings, where each character is 4
 *        bytes long (UTF8)
 *  @{ */
#define DISCORD_WEBHOOK_NAME_LEN 4 * 80 + 1
/** @} */

/** @defgroup DiscordCallbackTypes
 *  @{ */
typedef void (*discord_on_done)(struct discord *client, const void *obj);
typedef void (*discord_on_idle)(struct discord *client);
typedef void (*discord_on_application_command)(
  struct discord *client, const struct discord_application_command *app_cmd);
typedef void (*discord_on_channel)(struct discord *client,
                                   const struct discord_channel *channel);
typedef void (*discord_on_channel_pins_update)(
  struct discord *client,
  u64_snowflake_t guild_id,
  u64_snowflake_t channel_id,
  u64_unix_ms_t last_pin_timestamp);
typedef void (*discord_on_guild)(struct discord *client,
                                 const struct discord_guild *guild);
typedef void (*discord_on_guild_delete)(struct discord *client,
                                        u64_snowflake_t guild_id);
typedef void (*discord_on_guild_role)(struct discord *client,
                                      u64_snowflake_t guild_id,
                                      const struct discord_role *role);
typedef void (*discord_on_guild_role_delete)(struct discord *client,
                                             u64_snowflake_t guild_id,
                                             u64_snowflake_t role_id);
typedef void (*discord_on_guild_member)(
  struct discord *client,
  u64_snowflake_t guild_id,
  const struct discord_guild_member *member);
typedef void (*discord_on_guild_member_remove)(
  struct discord *client,
  u64_snowflake_t guild_id,
  const struct discord_user *user);
typedef void (*discord_on_guild_ban)(struct discord *client,
                                     u64_snowflake_t guild_id,
                                     const struct discord_user *user);
typedef void (*discord_on_interaction)(
  struct discord *client, const struct discord_interaction *interaction);
typedef void (*discord_on_message)(struct discord *client,
                                   const struct discord_message *message);
typedef void (*discord_on_message_delete)(struct discord *client,
                                          u64_snowflake_t id,
                                          u64_snowflake_t channel_id,
                                          u64_snowflake_t guild_id);
typedef void (*discord_on_message_delete_bulk)(struct discord *client,
                                               const u64_snowflake_t **ids,
                                               u64_snowflake_t channel_id,
                                               u64_snowflake_t guild_id);
typedef void (*discord_on_message_reaction_add)(
  struct discord *client,
  u64_snowflake_t user_id,
  u64_snowflake_t channel_id,
  u64_snowflake_t message_id,
  u64_snowflake_t guild_id,
  const struct discord_guild_member *member,
  const struct discord_emoji *emoji);
typedef void (*discord_on_message_reaction_remove)(
  struct discord *client,
  u64_snowflake_t user_id,
  u64_snowflake_t channel_id,
  u64_snowflake_t message_id,
  u64_snowflake_t guild_id,
  const struct discord_emoji *emoji);
typedef void (*discord_on_message_reaction_remove_all)(
  struct discord *client,
  u64_snowflake_t channel_id,
  u64_snowflake_t message_id,
  u64_snowflake_t guild_id);
typedef void (*discord_on_message_reaction_remove_emoji)(
  struct discord *client,
  u64_snowflake_t channel_id,
  u64_snowflake_t message_id,
  u64_snowflake_t guild_id,
  const struct discord_emoji *emoji);
typedef void (*discord_on_voice_state_update)(
  struct discord *client, const struct discord_voice_state *voice_state);
typedef void (*discord_on_voice_server_update)(struct discord *client,
                                               const char *token,
                                               u64_snowflake_t guild_id,
                                               const char *endpoint);
/** @} */

/** @defgroup OrcaDiscordCodes
 *  @{ */
/** Received a JSON error message */
#define ORCA_DISCORD_JSON_CODE 1
/** Bad authentication token */
#define ORCA_DISCORD_BAD_AUTH 2
/** Being ratelimited */
#define ORCA_DISCORD_RATELIMIT 3
/** Couldn't establish connection to Discord */
#define ORCA_DISCORD_CONNECTION 4
/** @} OrcaDiscordCodes */

/**
 * @brief Return the meaning of ORCAcode
 * @note if the client parameter is provided, the raw JSON error string will be
 *        given for ORCA_DISCORD_JSON_CODE code
 * @param code the ORCAcode to be explained
 * @param client the client created with discord_init(), NULL for generic error
 *        descriptions
 * @return a string containing the code meaning
 */
const char *discord_strerror(ORCAcode code, struct discord *client);

/**
 * @brief Create a Discord Client handle by its token
 *
 * @param token the bot token
 * @return the newly created Discord Client handle
 * @see discord_get_logconf() to configure logging behavior
 */
struct discord *discord_init(const char token[]);

/**
 * @brief Create a Discord Client handle by a bot.config file
 *
 * @param config_file the bot.config file name
 * @return the newly created Discord Client handle
 */
struct discord *discord_config_init(const char config_file[]);

/**
 * @brief Clone a discord client
 *
 * Should be called before entering a thread, to ensure each thread
 *        has its own client instance with unique buffers, url and headers.
 * @param orig_client the original client created with discord_init()
 * @return the original client clone
 */
struct discord *discord_clone(const struct discord *orig_client);

/**
 * @brief Free a Discord Client handle
 *
 * @param client the client created with discord_init()
 */
void discord_cleanup(struct discord *client);

/** @brief The async attributes for next request */
struct discord_async_attr {
  /** callback to be executed on a succesful request */
  discord_on_done done;
  /** whether the next request is high priority */
  bool high_p;
};

/**
 * @brief Set next request to run asynchronously
 *
 * @param client the client created with discord_init()
 * @param attr optional async attributes for next request, can be NULL if not
 *        needed
 */
void discord_async_next(struct discord *client,
                        struct discord_async_attr *attr);

/**
 * @brief Get the user structure corresponding to the client
 *
 * @param client the client created with discord_init()
 * @warning the returned structure should NOT be modified
 */
const struct discord_user *discord_get_self(struct discord *client);

/**
 * @brief Subscribe to Discord Gateway events
 *
 * @param client the client created with discord_init()
 * @param code the intents opcode, can be set as a bitmask operation
 */
void discord_add_intents(struct discord *client,
                         enum discord_gateway_intents code);
/**
 * @brief Unsubscribe from Discord Gateway events
 *
 * @param client the client created with discord_init()
 * @param code the intents opcode, can be set as bitmask operation
 *        Ex: 1 << 0 | 1 << 1 | 1 << 4
 *
 */
void discord_remove_intents(struct discord *client,
                            enum discord_gateway_intents code);
/**
 * @brief Set a mandatory prefix before commands
 *
 * Example: If @a 'help' is a command and @a '!' prefix is set, the command
 *       will only be validated if @a '!help' is sent
 * @param client the client created with discord_init()
 * @param prefix the prefix that should accompany any command
 * @see discord_set_on_command()
 */
void discord_set_prefix(struct discord *client, char *prefix);

/**
 * @brief Set command/callback pair.
 *
 * The callback is triggered when an user types the assigned command in a
 *        chat visible to the bot.
 * @param client the client created with discord_init()
 * @param command the command to trigger the callback
 * @param callback the callback to be triggered on event
 * @note The command and any subjacent empty space is left out of
 *       the message content
 */
void discord_set_on_command(struct discord *client,
                            char *command,
                            discord_on_message callback);

/**
 * @brief Set a variadic series of NULL terminated commands to a callback.
 *
 * The callback is triggered when a user types one of the assigned commands in
 *        chat visble to the bot.
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 * @param ... NULL terminated commands
 * @note The command and any subjacent empty space is left out of
 *       the message content
 */
void discord_set_on_commands(struct discord *client,
                             discord_on_message callback,
                             ...);

/** @defgroup DiscordCallbackSet
 * @brief Set callbacks to be triggered on event detection
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 * @note the functions will automatically set the necessary intent(s) to make
 *        the callback triggerable
 *  @{ */

/** @brief Triggers at every event-loop iteration.  */
void discord_set_on_idle(struct discord *client, discord_on_idle callback);
/** @brief Triggers when the client is ready */
void discord_set_on_ready(struct discord *client, discord_on_idle callback);
/** @brief Triggers when a application command is created */
void discord_set_on_application_command_create(
  struct discord *client, discord_on_application_command callback);
/** @brief Triggers when a application command is updated */
void discord_set_on_application_command_update(
  struct discord *client, discord_on_application_command callback);
/** @brief Triggers when a application command is deleted */
void discord_set_on_application_command_delete(
  struct discord *client, discord_on_application_command callback);
/** @brief Triggers when a channel is created */
void discord_set_on_channel_create(struct discord *client,
                                   discord_on_channel callback);
/** @brief Triggers when a channel is updated */
void discord_set_on_channel_update(struct discord *client,
                                   discord_on_channel callback);
/** @brief Triggers when a channel is deleted */
void discord_set_on_channel_delete(struct discord *client,
                                   discord_on_channel callback);
/** @brief Triggers when some channel pins are updated */
void discord_set_on_channel_pins_update(
  struct discord *client, discord_on_channel_pins_update callback);
/** @brief Triggers when a thread is created */
void discord_set_on_thread_create(struct discord *client,
                                  discord_on_channel callback);
/** @brief Triggers when a thread is updated */
void discord_set_on_thread_update(struct discord *client,
                                  discord_on_channel callback);
/** @brief Triggers when a thread is deleted */
void discord_set_on_thread_delete(struct discord *client,
                                  discord_on_channel callback);
/** @brief Triggers when a guild's information becomes available
 */
void discord_set_on_guild_create(struct discord *client,
                                 discord_on_guild callback);
/** @brief Triggers when a guild's information becomes updated */
void discord_set_on_guild_update(struct discord *client,
                                 discord_on_guild callback);
/** @brief Triggers when removed from a guild */
void discord_set_on_guild_delete(struct discord *client,
                                 discord_on_guild_delete callback);
/** @brief Triggers when a guild role is created */
void discord_set_on_guild_role_create(struct discord *client,
                                      discord_on_guild_role callback);
/** @brief Triggers when a guild role is updated */
void discord_set_on_guild_role_update(struct discord *client,
                                      discord_on_guild_role callback);
/** @brief Triggers when a guild role is deleted */
void discord_set_on_guild_role_delete(struct discord *client,
                                      discord_on_guild_role_delete callback);
/** @brief Triggers when a guild member is added */
void discord_set_on_guild_member_add(struct discord *client,
                                     discord_on_guild_member callback);
/** @brief Triggers when a guild member is updated */
void discord_set_on_guild_member_update(struct discord *client,
                                        discord_on_guild_member callback);
/** @brief Triggers when a guild member is removed */
void discord_set_on_guild_member_remove(
  struct discord *client, discord_on_guild_member_remove callback);
/** @brief Triggers when a guild ban is added */
void discord_set_on_guild_ban_add(struct discord *client,
                                  discord_on_guild_ban callback);
/** @brief Triggers when a guild ban is removed */
void discord_set_on_guild_ban_remove(struct discord *client,
                                     discord_on_guild_ban callback);
/** @brief Triggers when a interaction is created */
void discord_set_on_interaction_create(struct discord *client,
                                       discord_on_interaction callback);
/** @brief Triggers when a message is created */
void discord_set_on_message_create(struct discord *client,
                                   discord_on_message callback);
/** @brief Triggers when a message is updated */
void discord_set_on_message_update(struct discord *client,
                                   discord_on_message callback);
/** @brief Triggers when a message is deleted */
void discord_set_on_message_delete(struct discord *client,
                                   discord_on_message_delete callback);
/** @brief Triggers when a bulk of messages are deleted */
void discord_set_on_message_delete_bulk(
  struct discord *client, discord_on_message_delete_bulk callback);
/** @brief Triggers when a message reaction is added */
void discord_set_on_message_reaction_add(
  struct discord *client, discord_on_message_reaction_add callback);
/** @brief Triggers when a message reaction is removed */
void discord_set_on_message_reaction_remove(
  struct discord *client, discord_on_message_reaction_remove callback);
/** @brief Triggers when all reaction from some message is removed
 */
void discord_set_on_message_reaction_remove_all(
  struct discord *client, discord_on_message_reaction_remove_all callback);
/** @brief Triggers when all instances of a particular reaction from some
 *        message is removed */
void discord_set_on_message_reaction_remove_emoji(
  struct discord *client, discord_on_message_reaction_remove_emoji callback);
/** @brief Triggers when a voice state is updated */
void discord_set_on_voice_state_update(struct discord *client,
                                       discord_on_voice_state_update callback);
/** @brief Triggers when a voice server is updated */
void discord_set_on_voice_server_update(
  struct discord *client, discord_on_voice_server_update callback);

/** @} */

/**
 * @brief Helper to quickly set voice callbacks
 *
 * @param client the client created with discord_init()
 * @param callbacks the voice callbacks that will be executed
 */
void discord_set_voice_cbs(struct discord *client,
                           struct discord_voice_cbs *callbacks);

/**
 * @brief Start a connection to the Discord Gateway
 *
 * @param client the client created with discord_init()
 * @ORCA_return
 */
ORCAcode discord_run(struct discord *client);

/**
 * @brief Gracefully shutdown an ongoing Discord connection
 *
 * @param client the client created with discord_init()
 */
void discord_shutdown(struct discord *client);

/**
 * @brief Gracefully reconnects an ongoing Discord connection
 *
 * @param client the client created with discord_init()
 * @param resume true to attempt to resume to previous session,
 *        false restart a fresh session
 */
void discord_reconnect(struct discord *client, bool resume);

/**
 * @brief Store user arbitrary data that can be retrieved by discord_get_data()
 *
 * @param client the client created with discord_init()
 * @param data user arbitrary data
 * @return pointer to user data
 * @warning the user should provide his own locking mechanism to protect
 *        his data from race conditions
 */
void *discord_set_data(struct discord *client, void *data);

/**
 * @brief Receive user arbitrary data stored with discord_set_data()
 *
 * @param client the client created with discord_init()
 * @return pointer to user data
 * @warning the user should provide his own locking mechanism to protect
 *        his data from race conditions
 */
void *discord_get_data(struct discord *client);

/**
 * @brief Set the Client presence state
 *
 * @param client the client created with discord_init()
 * @param presence overwrite client's presence with it
 * @see discord_presence_add_activity()
 */
void discord_set_presence(struct discord *client,
                          struct discord_presence_status *presence);

/**
 * @brief Get the client WebSockets ping
 * @note Only works after a connection has been established via discord_run()
 *
 * @param client the client created with discord_init()
 * @return the ping in milliseconds
 */
int discord_get_ping(struct discord *client);

/**
 * @brief Get the current timestamp (in milliseconds)
 *
 * @param client the client created with discord_init()
 * @return the timestamp in milliseconds
 */
uint64_t discord_timestamp(struct discord *client);

/**
 * @brief Retrieve client's logging module for configuration purposes
 *
 * @param client the client created with discord_init()
 * @return the client's logging module
 * @see logconf_setup(), logconf_set_quiet(), logconf_set_level()
 */
struct logconf *discord_get_logconf(struct discord *client);

/******************************************************************************
 * Functions specific to Discord's REST API
 ******************************************************************************/

/**
 * Fetch all of the global commands for your application. Returns an array of
 *       application command objects.
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @ORCA_ret_list{ret, application command}
 * @ORCA_return
 */
ORCAcode discord_get_global_application_commands(
  struct discord *client,
  u64_snowflake_t application_id,
  struct discord_application_command ***ret);

/**
 * Create a new global command. New global commands will be available in all
 *       guilds after 1 hour.
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param params request parameters
 * @ORCA_ret_obj{ret, application command}
 * @ORCA_return
 */
ORCAcode discord_create_global_application_command(
  struct discord *client,
  u64_snowflake_t application_id,
  struct discord_create_global_application_command_params *params,
  struct discord_application_command *ret);

/**
 * Fetch a global command for your application. Returns an application command
 *       object.
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param command_id the registered command id
 * @ORCA_ret_obj{ret, application command}
 * @ORCA_return
 */
ORCAcode discord_get_global_application_command(
  struct discord *client,
  u64_snowflake_t application_id,
  u64_snowflake_t command_id,
  struct discord_application_command *ret);

/**
 * Edit a global command. Updates will be available in all guilds
 *       after 1 hour. Returns an application command object.
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param command_id the registered command id
 * @param params request parameters
 * @ORCA_ret_obj{ret, application command}
 * @ORCA_return
 */
ORCAcode discord_edit_global_application_command(
  struct discord *client,
  u64_snowflake_t application_id,
  u64_snowflake_t command_id,
  struct discord_edit_global_application_command_params *params,
  struct discord_application_command *ret);

/**
 * Deletes a global command.
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param command_id the registered command id
 * @ORCA_return
 */
ORCAcode discord_delete_global_application_command(
  struct discord *client,
  u64_snowflake_t application_id,
  u64_snowflake_t command_id);

/**
 * Takes a list of application commands, overwriting existing commands
 *       that are registered globally for this application. Updates will be
 *       available in all guilds after 1 hour. Returns a list of application
 *       command objects. Commands that do not already exist will count
 *       toward daily application command create limits.
 * @warning This will overwrite all types of application commands: slash
 *        commands, user commands, and message commands.
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param params the request parameters, a list of application commands
 * @ORCA_ret_list{ret, application command}
 * @ORCA_return
 */
ORCAcode discord_bulk_overwrite_global_application_command(
  struct discord *client,
  u64_snowflake_t application_id,
  struct discord_application_command **params,
  struct discord_application_command ***ret);

/**
 * Fetch all of the guild commands for your application for a specific guild.
 * Returns an array of application command objects.
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the commands are located
 * @ORCA_ret_list{ret, application command}
 * @ORCA_return
 */
ORCAcode discord_get_guild_application_commands(
  struct discord *client,
  u64_snowflake_t application_id,
  u64_snowflake_t guild_id,
  struct discord_application_command ***ret);

/**
 * Create a new guild command. New guild commands will be available in
 *       the guild immediately. Returns an application command object. If
 *       the command did not already exist, it will count toward daily
 *       application command create limits.
 * @note Creating a command with the same name as an existing command for your
 *        application will overwrite the old command.
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the command is located
 * @param params request parameters
 * @ORCA_ret_obj{ret, application command}
 * @ORCA_return
 */
ORCAcode discord_create_guild_application_command(
  struct discord *client,
  u64_snowflake_t application_id,
  u64_snowflake_t guild_id,
  struct discord_create_guild_application_command_params *params,
  struct discord_application_command *ret);

/**
 * Fetch a guild command for your application. Returns an application command
 *       object.
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the command is located
 * @param command_id the registered command id
 * @ORCA_ret_obj{ret, application command}
 * @ORCA_return
 */
ORCAcode discord_get_guild_application_command(
  struct discord *client,
  u64_snowflake_t application_id,
  u64_snowflake_t guild_id,
  u64_snowflake_t command_id,
  struct discord_application_command *ret);

/**
 * Edit a guild command. Updates for guild commands will be available
 *       immediately. Returns an application command object.
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the command is located
 * @param command_id the registered command id
 * @param params request parameters
 * @ORCA_ret_obj{ret, application command}
 * @ORCA_return
 */
ORCAcode discord_edit_guild_application_command(
  struct discord *client,
  u64_snowflake_t application_id,
  u64_snowflake_t guild_id,
  u64_snowflake_t command_id,
  struct discord_edit_guild_application_command_params *params,
  struct discord_application_command *ret);

/**
 * Deletes a guild command.
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the command is located
 * @param command_id the registered command id
 * @ORCA_return
 */
ORCAcode discord_delete_guild_application_command(
  struct discord *client,
  u64_snowflake_t application_id,
  u64_snowflake_t guild_id,
  u64_snowflake_t command_id);

/**
 * Takes a list of application commands, overwriting existing commands
 *       for the guild. Returns a list of application command objects.
 * @warning This will overwrite all types of application commands: slash
 *        commands, user commands, and message commands.
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the commands are located
 * @param params the request parameters, a list of application commands
 * @ORCA_ret_list{ret, application command}
 * @ORCA_return
 */
ORCAcode discord_bulk_overwrite_guild_application_command(
  struct discord *client,
  u64_snowflake_t application_id,
  u64_snowflake_t guild_id,
  struct discord_application_command **params,
  struct discord_application_command ***ret);

/**
 * Fetches command permissions for all commands for your application in a
 *       guild. Returns an array of guild application command permissions
 * objects.
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the commands are located
 * @ORCA_ret_list{ret, guild application command permissions}
 * @ORCA_return
 */
ORCAcode discord_get_guild_application_command_permissions(
  struct discord *client,
  u64_snowflake_t application_id,
  u64_snowflake_t guild_id,
  struct discord_guild_application_command_permissions ***ret);

/**
 * Fetches command permissions for a specific command for your application in a
 *       guild. Returns a guild application command permissions object.
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the command is located
 * @param command_id the registered command id
 * @ORCA_ret_obj{ret, application command permissions}
 * @ORCA_return
 */
ORCAcode discord_get_application_command_permissions(
  struct discord *client,
  u64_snowflake_t application_id,
  u64_snowflake_t guild_id,
  u64_snowflake_t command_id,
  struct discord_guild_application_command_permissions *ret);

/**
 * Edits command permissions for a specific command for your application in a
 *       guild. You can only add up to 10 permission overwrites for a command.
 * Returns a guild application command permissions object.
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the commands are located
 * @param command_id the registered command id
 * @param params the request parameters
 * @ORCA_ret_obj{ret, application command permissions}
 * @ORCA_return
 */
ORCAcode discord_edit_application_command_permissions(
  struct discord *client,
  u64_snowflake_t application_id,
  u64_snowflake_t guild_id,
  u64_snowflake_t command_id,
  struct discord_edit_application_command_permissions_params *params,
  struct discord_guild_application_command_permissions *ret);

/**
 * Batch edits permissions for all commands in a guild. Takes an array
 *       of partial guild application command permissions objects including
 *       id and permissions.
 * You can only add up to 10 permission overwrites for a command.
 * Returns an array of GuildApplicationCommandPermissions objects.
 * @warning This will overwrite all types of application commands: slash
 *       commands, user commands, and message commands.
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the commands are located
 * @param params the request parameters, a list of guild application commands
 *       permissions
 * @ORCA_ret_list{ret, guild application command permissions}
 * @ORCA_return
 */
ORCAcode discord_batch_edit_application_command_permissions(
  struct discord *client,
  u64_snowflake_t application_id,
  u64_snowflake_t guild_id,
  struct discord_guild_application_command_permissions **params,
  struct discord_guild_application_command_permissions ***ret);

/**
 * Create a response to an Interaction from the gateway. Takes an interaction
 *       response.
 * @param client the client created with discord_init()
 * @param interaction_id the unique id of the interaction
 * @param interaction_token the unique token of the interaction
 * @param params the request parameters
 * @ORCA_ret_obj{ret, interaction response}
 * @ORCA_return
 */
ORCAcode discord_create_interaction_response(
  struct discord *client,
  u64_snowflake_t interaction_id,
  const char interaction_token[],
  struct discord_interaction_response *params,
  struct discord_interaction_response *ret);

/**
 * Returns the initial Interaction response.
 * @param client the client created with discord_init()
 * @param interaction_id the unique id of the interaction
 * @param interaction_token the unique token of the interaction
 * @ORCA_ret_obj{ret, interaction response}
 * @ORCA_return
 */
ORCAcode discord_get_original_interaction_response(
  struct discord *client,
  u64_snowflake_t interaction_id,
  const char interaction_token[],
  struct discord_interaction_response *ret);

/**
 * Edit the initial Interaction response.
 * @param client the client created with discord_init()
 * @param interaction_id the unique id of the interaction
 * @param interaction_token the unique token of the interaction
 * @param params request parameters
 * @ORCA_ret_obj{ret, interaction response}
 * @ORCA_return
 */
ORCAcode discord_edit_original_interaction_response(
  struct discord *client,
  u64_snowflake_t interaction_id,
  const char interaction_token[],
  struct discord_edit_original_interaction_response_params *params,
  struct discord_interaction_response *ret);

/**
 * Delete the initial Interaction response.
 * @param client the client created with discord_init()
 * @param interaction_id the unique id of the interaction
 * @param interaction_token the unique token of the interaction
 * @ORCA_return
 */
ORCAcode discord_delete_original_interaction_response(
  struct discord *client,
  u64_snowflake_t interaction_id,
  const char interaction_token[]);

/**
 * Create a followup message for an Interaction.
 * @param client the client created with discord_init()
 * @param application_id the unique id of the application
 * @param interaction_token the unique token of the interaction
 * @param params request parameters
 * @ORCA_ret_obj{ret, webhook}
 * @ORCA_return
 */
ORCAcode discord_create_followup_message(
  struct discord *client,
  u64_snowflake_t application_id,
  const char interaction_token[],
  struct discord_create_followup_message_params *params,
  struct discord_webhook *ret);

/**
 * Returns a followup message for an interaction.
 * @param client the client created with discord_init()
 * @param application_id the unique id of the application
 * @param interaction_token the unique token of the interaction
 * @param message_id the unique id of the message
 * @ORCA_ret_obj{ret, message}
 * @ORCA_return
 */
ORCAcode discord_get_followup_message(struct discord *client,
                                      u64_snowflake_t application_id,
                                      const char interaction_token[],
                                      u64_snowflake_t message_id,
                                      struct discord_message *ret);

/**
 * Edits a followup message for an interaction.
 * @param client the client created with discord_init()
 * @param application_id the unique id of the application
 * @param interaction_token the unique token of the interaction
 * @param message_id the unique id of the message
 * @param params request parameters
 * @ORCA_ret_obj{ret, message}
 * @ORCA_return
 */
ORCAcode discord_edit_followup_message(
  struct discord *client,
  u64_snowflake_t application_id,
  const char interaction_token[],
  u64_snowflake_t message_id,
  struct discord_edit_followup_message_params *params,
  struct discord_message *ret);

/**
 * Edits a followup message for an interaction.
 * @param client the client created with discord_init()
 * @param application_id the unique id of the application
 * @param interaction_token the unique token of the interaction
 * @param message_id the unique id of the message
 * @ORCA_return
 */
ORCAcode discord_delete_followup_message(struct discord *client,
                                         u64_snowflake_t application_id,
                                         const char interaction_token[],
                                         u64_snowflake_t message_id);

/**
 * Returns an audit log object for the guild.
 * @note Requires the 'VIEW_AUDIT_LOG' permission
 * @param client the client created with discord_init()
 * @param guild_id the guild to retrieve the audit log from
 * @param params request parameters
 * @ORCA_ret_obj{ret, audit log}
 * @ORCA_return
 */
ORCAcode discord_get_guild_audit_log(
  struct discord *client,
  u64_snowflake_t guild_id,
  struct discord_get_guild_audit_log_params *params,
  struct discord_audit_log *ret);

/**
 * Get a channel by ID. Returns a channel object. If the channel is a thread, a
 *       thread member object is included in the returned result.
 * @param client the client created with discord_init()
 * @param channel_id the channel to be retrieved
 * @ORCA_ret_obj{ret, channel}
 * @ORCA_return
 */
ORCAcode discord_get_channel(struct discord *client,
                             u64_snowflake_t channel_id,
                             struct discord_channel *ret);

/**
 * Update a channel's settings.
 * @param client the client created with discord_init()
 * @param channel_id the channel to be modified
 * @param params request parameters
 * @ORCA_ret_obj{ret, channel}
 * @ORCA_return
 */
ORCAcode discord_modify_channel(struct discord *client,
                                u64_snowflake_t channel_id,
                                struct discord_modify_channel_params *params,
                                struct discord_channel *ret);

/**
 * Delete a channel, or close a private message.
 * @note Requires the MANAGE_CHANNELS permission for the guild, or
 * MANAGE_THREADS if the channel is a thread. Deleting a category does not
 *       delete its child channels; they will have their parent_id removed and
 * a Channel Update Gateway event will fire for each of them.
 * @note Fires a Channel Delete Gateway event (or Thread Delete if the channel
 *       was a thread).
 * @param client the client created with discord_init()
 * @param channel_id the channel to be deleted
 * @ORCA_ret_obj{ret, channel}
 * @ORCA_return
 */
ORCAcode discord_delete_channel(struct discord *client,
                                u64_snowflake_t channel_id,
                                struct discord_channel *ret);

/**
 * Returns the messages for a channel.
 * @note If operating on a guild channel, this endpoint requires the
 * VIEW_CHANNEL permission to be present on the current user.
 * @note If the current user is missing the 'READ_MESSAGE_HISTORY' permission
 *       in the channel then this will return no messages (since they cannot
 * read the message history).
 * @note The before, after, and around keys are mutually exclusive, only one
 *       may be passed at a time.
 * @param client the client created with discord_init()
 * @param channel_id the channel to get messages from
 * @param params request parameters
 * @ORCA_ret_list{ret, message}
 * @ORCA_return
 */
ORCAcode discord_get_channel_messages(
  struct discord *client,
  u64_snowflake_t channel_id,
  struct discord_get_channel_messages_params *params,
  struct discord_message ***ret);

/**
 * Returns a specific message in the channel.
 * @note If operating on a guild channel, this endpoint requires the
 * 'READ_MESSAGE_HISTORY' permission to be present on the current user.
 * @param client the client created with discord_init()
 * @param channel_id the channel where the message resides
 * @param message_id the message itself
 * @ORCA_ret_obj{ret, message}
 * @ORCA_return
 */
ORCAcode discord_get_channel_message(struct discord *client,
                                     u64_snowflake_t channel_id,
                                     u64_snowflake_t message_id,
                                     struct discord_message *ret);

/**
 * Post a message to a guild text or DM channel. Fires a Message Create Gateway
 *       event.
 * @param client the client created with discord_init()
 * @param channel_id the channel to send the message at
 * @param params request parameters
 * @ORCA_ret_obj{ret, message}
 * @ORCA_return
 */
ORCAcode discord_create_message(struct discord *client,
                                u64_snowflake_t channel_id,
                                struct discord_create_message_params *params,
                                struct discord_message *ret);

/**
 * Crosspost a message in a News Channel to following channels. This endpoint
 *       requires the 'SEND_MESSAGES' permission, if the current user sent the
 *       message, or additionally the 'MANAGE_MESSAGES' permission, for all
 * other messages, to be present for the current user.
 * @param client the client created with discord_init()
 * @param channel_id the news channel that will crosspost
 * @param message_id the message that will crospost
 * @ORCA_ret_obj{ret, message}
 * @ORCA_return
 */
ORCAcode discord_crosspost_message(struct discord *client,
                                   u64_snowflake_t channel_id,
                                   u64_snowflake_t message_id,
                                   struct discord_message *ret);

/**
 * Create a reaction for the message.
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message to receive a reaction
 * @param emoji_id the emoji id (leave as 0 if not a custom emoji)
 * @param emoji_name the emoji name
 * @ORCA_return
 */
ORCAcode discord_create_reaction(struct discord *client,
                                 u64_snowflake_t channel_id,
                                 u64_snowflake_t message_id,
                                 u64_snowflake_t emoji_id,
                                 const char emoji_name[]);

/**
 * Delete a reaction the current user has made for the message.
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message to have a reaction deleted
 * @param emoji_id the emoji id (leave as 0 if not a custom emoji)
 * @param emoji_name the emoji name
 * @ORCA_return
 */
ORCAcode discord_delete_own_reaction(struct discord *client,
                                     u64_snowflake_t channel_id,
                                     u64_snowflake_t message_id,
                                     u64_snowflake_t emoji_id,
                                     const char emoji_name[]);

/**
 * Deletes another user's reaction.
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message to have a reaction deleted
 * @param user_id the user the reaction belongs to
 * @param emoji_id the emoji id (leave as 0 if not a custom emoji)
 * @param emoji_name the emoji name
 * @ORCA_return
 */
ORCAcode discord_delete_user_reaction(struct discord *client,
                                      u64_snowflake_t channel_id,
                                      u64_snowflake_t message_id,
                                      u64_snowflake_t user_id,
                                      u64_snowflake_t emoji_id,
                                      const char emoji_name[]);

/**
 * Get a list of users that reacted with this emoji.
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message reacted to
 * @param emoji_id the emoji id (leave as 0 if not a custom emoji)
 * @param emoji_name the emoji name
 * @param params request parameters
 * @ORCA_ret_list{ret, user}
 * @ORCA_return
 */
ORCAcode discord_get_reactions(struct discord *client,
                               u64_snowflake_t channel_id,
                               u64_snowflake_t message_id,
                               u64_snowflake_t emoji_id,
                               const char emoji_name[],
                               struct discord_get_reactions_params *params,
                               struct discord_user ***ret);

/**
 * Deletes all reactions on a message.
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message that will be purged of reactions
 * @ORCA_return
 */
ORCAcode discord_delete_all_reactions(struct discord *client,
                                      u64_snowflake_t channel_id,
                                      u64_snowflake_t message_id);

/**
 * Deletes all the reactions for a given emoji on a message.
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message that will be purged of reactions from
 *       particular emoji
 * @param emoji_id the emoji id (leave as 0 if not a custom emoji)
 * @param emoji_name the emoji name
 * @ORCA_return
 */
ORCAcode discord_delete_all_reactions_for_emoji(struct discord *client,
                                                u64_snowflake_t channel_id,
                                                u64_snowflake_t message_id,
                                                u64_snowflake_t emoji_id,
                                                const char emoji_name[]);

/**
 * Edit a previously sent message.
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message that will be purged of reactions from
 *       particular emoji
 * @param params request parameters
 * @ORCA_ret_obj{ret, message}
 * @ORCA_return
 */
ORCAcode discord_edit_message(struct discord *client,
                              u64_snowflake_t channel_id,
                              u64_snowflake_t message_id,
                              struct discord_edit_message_params *params,
                              struct discord_message *ret);

/**
 * Delete a message.
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message that will be purged of reactions from
 *       particular emoji
 * @ORCA_return
 */
ORCAcode discord_delete_message(struct discord *client,
                                u64_snowflake_t channel_id,
                                u64_snowflake_t message_id);

/**
 * Delete multiple messages in a single request.
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param messages the null-terminated list of messages to be deleted
 * @ORCA_return
 */
ORCAcode discord_bulk_delete_messages(struct discord *client,
                                      u64_snowflake_t channel_id,
                                      u64_snowflake_t **messages);

/**
 * Edit the channel permission overwrites for a user or role in a channel.
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param overwrite_id
 * @param params request parameters
 * @ORCA_return
 */
ORCAcode discord_edit_channel_permissions(
  struct discord *client,
  u64_snowflake_t channel_id,
  u64_snowflake_t overwrite_id,
  struct discord_edit_channel_permissions_params *params);

/**
 * Returns a list of invite objects (with invite metadata) for the channel.
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @ORCA_ret_list{ret, invite}
 * @ORCA_return
 */
ORCAcode discord_get_channel_invites(struct discord *client,
                                     u64_snowflake_t channel_id,
                                     struct discord_invite ***ret);

/**
 * Create a new invite object for the channel.
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param params request parameters
 * @ORCA_ret_obj{ret, invite}
 * @ORCA_return
 */
ORCAcode discord_create_channel_invite(
  struct discord *client,
  u64_snowflake_t channel_id,
  struct discord_create_channel_invite_params *params,
  struct discord_invite *ret);

/**
 * Delete a channel permission overwrite for a user or role in a channel.
 * @param client the client created with discord_init()
 * @param channel_id the channel to the permission deleted
 * @param overwrite_id the id of the overwritten permission
 * @ORCA_return
 */
ORCAcode discord_delete_channel_permission(struct discord *client,
                                           u64_snowflake_t channel_id,
                                           u64_snowflake_t overwrite_id);

ORCAcode discord_trigger_typing_indicator(struct discord *client,
                                          u64_snowflake_t channel_id);

ORCAcode discord_follow_news_channel(
  struct discord *client,
  u64_snowflake_t channel_id,
  struct discord_follow_news_channel_params *params,
  struct discord_channel *ret);

ORCAcode discord_get_pinned_messages(struct discord *client,
                                     u64_snowflake_t channel_id,
                                     struct discord_message ***ret);

/**
 * Pin a message in a channel.
 * @param client the client created with discord_init()
 * @param channel_id channel to pin the message on
 * @param message_id message to be pinned
 * @ORCA_return
 */
ORCAcode discord_pin_message(struct discord *client,
                             u64_snowflake_t channel_id,
                             u64_snowflake_t message_id);

/**
 * Unpin a message in a channel.
 * @param client the client created with discord_init()
 * @param channel_id channel for the message to be unpinned
 * @param message_id message to be unpinned
 * @ORCA_return
 */
ORCAcode discord_unpin_message(struct discord *client,
                               u64_snowflake_t channel_id,
                               u64_snowflake_t message_id);

/**
 * Adds a recipient to a Group DM using their access token.
 * @param client the client created with discord_init()
 * @param channel_id group to add the user in
 * @param user_id user to be added
 * @param params request parameters
 * @ORCA_return
 */
ORCAcode discord_group_dm_add_recipient(
  struct discord *client,
  u64_snowflake_t channel_id,
  u64_snowflake_t user_id,
  struct discord_group_dm_add_recipient_params *params);

/** @brief @b DELETE /channels/{channel.id}/recipients/{user.id}
 *
 * Removes a recipient from a Group DM.
 * @param client the client created with discord_init()
 * @param channel_id channel for the user to be removed from
 * @param user_id user to be removed
 */
ORCAcode discord_group_dm_remove_recipient(struct discord *client,
                                           u64_snowflake_t channel_id,
                                           u64_snowflake_t user_id);

/** @brief @b POST /channels/{channel.id}/messages/{message.id}/threads
 *
 * Creates a new thread from an existing message.
 * @param client the client created with discord_init()
 * @param channel_id channel to start a thread on
 * @param message_id message to start a thread from
 * @param params request parameters
 * @ORCA_ret_obj{ret, thread channel}
 * @ORCA_return
 */
ORCAcode discord_start_thread_with_message(
  struct discord *client,
  u64_snowflake_t channel_id,
  u64_snowflake_t message_id,
  struct discord_start_thread_with_message_params *params,
  struct discord_channel *ret);

ORCAcode discord_start_thread_without_message(
  struct discord *client,
  u64_snowflake_t channel_id,
  struct discord_start_thread_without_message_params *params,
  struct discord_channel *ret);

ORCAcode discord_join_thread(struct discord *client,
                             u64_snowflake_t channel_id);

ORCAcode discord_add_thread_member(struct discord *client,
                                   u64_snowflake_t channel_id,
                                   u64_snowflake_t user_id);

ORCAcode discord_leave_thread(struct discord *client,
                              u64_snowflake_t channel_id);

ORCAcode discord_remove_thread_member(struct discord *client,
                                      u64_snowflake_t channel_id,
                                      u64_snowflake_t user_id);

ORCAcode discord_list_thread_members(struct discord *client,
                                     u64_snowflake_t channel_id,
                                     struct discord_thread_member ***ret);

ORCAcode discord_list_active_threads(
  struct discord *client,
  u64_snowflake_t channel_id,
  struct discord_thread_response_body *body);

ORCAcode discord_list_public_archived_threads(
  struct discord *client,
  u64_snowflake_t channel_id,
  u64_unix_ms_t before,
  int limit,
  struct discord_thread_response_body *body);

ORCAcode discord_list_private_archived_threads(
  struct discord *client,
  u64_snowflake_t channel_id,
  u64_unix_ms_t before,
  int limit,
  struct discord_thread_response_body *body);

ORCAcode discord_list_joined_private_archived_threads(
  struct discord *client,
  u64_snowflake_t channel_id,
  u64_unix_ms_t before,
  int limit,
  struct discord_thread_response_body *body);

ORCAcode discord_list_guild_emojis(struct discord *client,
                                   u64_snowflake_t guild_id,
                                   struct discord_emoji ***ret);

ORCAcode discord_get_guild_emoji(struct discord *client,
                                 u64_snowflake_t guild_id,
                                 u64_snowflake_t emoji_id,
                                 struct discord_emoji *ret);

ORCAcode discord_create_guild_emoji(
  struct discord *client,
  u64_snowflake_t guild_id,
  struct discord_create_guild_emoji_params *params,
  struct discord_emoji *ret);

ORCAcode discord_modify_guild_emoji(
  struct discord *client,
  u64_snowflake_t guild_id,
  u64_snowflake_t emoji_id,
  struct discord_modify_guild_emoji_params *params,
  struct discord_emoji *ret);

ORCAcode discord_delete_guild_emoji(struct discord *client,
                                    u64_snowflake_t guild_id,
                                    u64_snowflake_t emoji_id);

ORCAcode discord_create_guild(struct discord *client,
                              struct discord_create_guild_params *params,
                              struct discord_guild *ret);

/**
 * Returns the guild object for the given id. If with_counts is set to true,
 *       this endpoint will also return approximate_member_count and
 *       approximate_presence_count for the guild.
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to retrieve
 * @ORCA_ret_obj{ret, guild preview}
 * @ORCA_return
 */
ORCAcode discord_get_guild(struct discord *client,
                           u64_snowflake_t guild_id,
                           struct discord_guild *ret);

ORCAcode discord_get_guild_preview(struct discord *client,
                                   u64_snowflake_t guild_id,
                                   struct discord_guild_preview *ret);

/**
 * Modify a guild's settings. Requires the MANAGE_GUILD permission. Returns the
 *       updated guild object on success. Fires a Guild Update Gateway event.
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to modify
 * @param params request parameters
 * @ORCA_ret_obj{ret, guild}
 * @ORCA_return
 */
ORCAcode discord_modify_guild(struct discord *client,
                              u64_snowflake_t guild_id,
                              struct discord_modify_guild_params *params,
                              struct discord_guild *ret);

/**
 * Delete a guild permanently. User must be owner. Returns 204 No Content on
 *       success. Fires a Guild Delete Gateway event.
 * @param client the client created with discord_init()
 * @param guild_id id of guild to delete
 * @ORCA_return
 */
ORCAcode discord_delete_guild(struct discord *client,
                              u64_snowflake_t guild_id);

/**
 * Returns a list of guild channel objects. Does not include threads.
 * @param client the client created with discord_init()
 * @param guild_id id of guild to fetch channels from
 * @ORCA_ret_list{ret, channel}
 * @ORCA_return
 */
ORCAcode discord_get_guild_channels(struct discord *client,
                                    u64_snowflake_t guild_id,
                                    struct discord_channel ***ret);

/**
 * Create a new channel object for the guild. Requires the MANAGE_CHANNELS
 *       permission. If setting permission overwrites, only permissions your
 * bot has in the guild can be allowed/denied. Setting MANAGE_ROLES permission
 * in channels is only possible for guild administrators. Returns the new
 * channel object on success. Fires a Channel Create Gateway event.
 * @param client the client created with discord_init()
 * @param guild_id id of the guild to create a channel at
 * @param params request parameters
 * @ORCA_ret_obj{ret, channel}
 * @ORCA_return
 */
ORCAcode discord_create_guild_channel(
  struct discord *client,
  u64_snowflake_t guild_id,
  struct discord_create_guild_channel_params *params,
  struct discord_channel *ret);

/**
 * Modify the positions of a set of channel objects for the guild. Requires
 * MANAGE_CHANNELS permission. Returns a 204 empty response on success. Fires
 *       multiple Channel Update Gateway events.
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to change the positions of the
 *       channels in
 * @param params request parameters
 * @ORCA_return
 */
ORCAcode discord_modify_guild_channel_positions(
  struct discord *client,
  u64_snowflake_t guild_id,
  struct discord_modify_guild_channel_positions_params **params);

ORCAcode discord_get_guild_member(struct discord *client,
                                  u64_snowflake_t guild_id,
                                  u64_snowflake_t user_id,
                                  struct discord_guild_member *ret);

ORCAcode discord_list_guild_members(
  struct discord *client,
  u64_snowflake_t guild_id,
  struct discord_list_guild_members_params *params,
  struct discord_guild_member ***ret);

ORCAcode discord_search_guild_members(
  struct discord *client,
  u64_snowflake_t guild_id,
  struct discord_search_guild_members_params *params,
  struct discord_guild_member ***ret);

ORCAcode discord_modify_guild_member(
  struct discord *client,
  u64_snowflake_t guild_id,
  u64_snowflake_t user_id,
  struct discord_modify_guild_member_params *params,
  struct discord_guild_member *ret);

ORCAcode discord_add_guild_member(
  struct discord *client,
  u64_snowflake_t guild_id,
  u64_snowflake_t user_id,
  struct discord_add_guild_member_params *params,
  struct discord_guild_member *ret);

/**
 * Modifies the current member in the guild. Used to modify nicknames.
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild where the member exists
 * @param params the parameters sent to discord. For example the new nickname
 *       for the bot
 * @ORCA_ret_obj{ret, guild member}
 *       successful
 * @ORCA_return
 */
ORCAcode discord_modify_current_member(
  struct discord *client,
  u64_snowflake_t guild_id,
  struct discord_modify_current_member_params *params,
  struct discord_guild_member *ret);

/**
 * @deprecated use discord_modify_current_member() instead
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild where the member exists
 * @param params the new nickname for the bot
 * @ORCA_ret_obj{ret, guild member}
 * @ORCA_return
 */
ORCAcode discord_modify_current_user_nick(
  struct discord *client,
  u64_snowflake_t guild_id,
  struct discord_modify_current_user_nick_params *params,
  struct discord_guild_member *ret);

/**
 * Adds a role to a guild member.
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild where the member exists
 * @param user_id the unique id of the user
 * @param role_id the unique id of the role to be added
 * @ORCA_return
 */
ORCAcode discord_add_guild_member_role(struct discord *client,
                                       u64_snowflake_t guild_id,
                                       u64_snowflake_t user_id,
                                       u64_snowflake_t role_id);

/**
 * Removes a role from a guild member.
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild where the member exists
 * @param user_id the unique id of the user
 * @param role_id the unique id of the role to be removed
 * @ORCA_return
 */
ORCAcode discord_remove_guild_member_role(struct discord *client,
                                          u64_snowflake_t guild_id,
                                          u64_snowflake_t user_id,
                                          u64_snowflake_t role_id);

/**
 * Remove a member from a guild.
 * @param client the client created with discord_init()
 * @param guild_id the guild to remove the member from
 * @param user_id the user to be removed
 * @ORCA_return
 */
ORCAcode discord_remove_guild_member(struct discord *client,
                                     u64_snowflake_t guild_id,
                                     u64_snowflake_t user_id);

/**
 * Returns a list of ban objects for the users banned from this guild.
 * @param client the client created with discord_init()
 * @param guild_id the guild to get the list from
 * @ORCA_ret_list{ret, ban}
 * @ORCA_return
 */
ORCAcode discord_get_guild_bans(struct discord *client,
                                u64_snowflake_t guild_id,
                                struct discord_ban ***ret);

/**
 * Returns a ban object for the given user or a 404 not found if the ban cannot
 *       be found.
 * @param client the client created with discord_init()
 * @param guild_id the guild to return the ban from
 * @param user_id the user that is banned
 * @ORCA_ret_obj{ret, ban}
 * @ORCA_return
 */
ORCAcode discord_get_guild_ban(struct discord *client,
                               u64_snowflake_t guild_id,
                               u64_snowflake_t user_id,
                               struct discord_ban *ret);

ORCAcode discord_create_guild_ban(
  struct discord *client,
  u64_snowflake_t guild_id,
  u64_snowflake_t user_id,
  struct discord_create_guild_ban_params *params);

ORCAcode discord_remove_guild_ban(struct discord *client,
                                  u64_snowflake_t guild_id,
                                  u64_snowflake_t user_id);

ORCAcode discord_get_guild_roles(struct discord *client,
                                 u64_snowflake_t guild_id,
                                 struct discord_role ***ret);

ORCAcode discord_create_guild_role(
  struct discord *client,
  u64_snowflake_t guild_id,
  struct discord_create_guild_role_params *params,
  struct discord_role *ret);

/**
 * Begin a guild prune. Discord recommends for larger servers to set
 * "compute_prune_count" to false. Requires the KICK_MEMBERS permission.
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to start the prune
 * @ORCA_return
 */
ORCAcode discord_begin_guild_prune(
  struct discord *client,
  u64_snowflake_t guild_id,
  struct discord_begin_guild_prune_params *params);

/**
 * Returns a list of invite objects (with invite metadata) for the guild.
 * Requires the MANAGE_GUILD permission.
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to get invites from
 * @ORCA_ret_list{ret, invite}
 * @ORCA_return
 */
ORCAcode discord_get_guild_invites(struct discord *client,
                                   u64_snowflake_t guild_id,
                                   struct discord_invite ***ret);

/**
 * Deletes the integration for the guild. It will also delete any associated
 *       webhooks and bots. Requires the MANAGE_GUILD permission.
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to delete the integrations from
 * @param integration_id the id of the integration to delete
 * @ORCA_return
 */
ORCAcode discord_delete_guild_integrations(struct discord *client,
                                           u64_snowflake_t guild_id,
                                           u64_snowflake_t integration_id);

/**
 * Returns a partial invite object from the guild. Requires the MANAGE_GUILD
 *       permission.
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to get vanity url from
 * @ORCA_ret_obj{ret, invite}
 * @ORCA_return
 */
ORCAcode discord_get_guild_vanity_url(struct discord *client,
                                      u64_snowflake_t guild_id,
                                      struct discord_invite *ret);

/**
 * Returns the Welcome Screen object for the guild.
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to get welcome screen of
 * @ORCA_ret_obj{ret, guild welcome screen}
 * @ORCA_return
 */
ORCAcode discord_get_guild_welcome_screen(struct discord *client,
                                          u64_snowflake_t guild_id,
                                          struct discord_welcome_screen *ret);

ORCAcode discord_modify_guild_role_positions(
  struct discord *client,
  u64_snowflake_t guild_id,
  struct discord_modify_guild_role_positions_params **params,
  struct discord_role ***ret);

/**
 * Modify a guild role. Requires the MANAGE_ROLES permission. Returns the
 *       updated role on success. Fires a Guild Role Update Gateway event.
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild that the role belongs to
 * @param role_id the unique id of the role to modify
 * @param params request parameters
 * @ORCA_ret_obj{ret, role}
 * @ORCA_return
 */
ORCAcode discord_modify_guild_role(
  struct discord *client,
  u64_snowflake_t guild_id,
  u64_snowflake_t role_id,
  struct discord_modify_guild_role_params *params,
  struct discord_role *ret);

/**
 * Delete a guild role. Requires the MANAGE_ROLES permission. Returns a 204
 *       empty response on success. Fires a Guild Role Delete Gateway event.
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild that the role belongs to
 * @param role_id the unique id of the role to delete
 * @ORCA_return
 */
ORCAcode discord_delete_guild_role(struct discord *client,
                                   u64_snowflake_t guild_id,
                                   u64_snowflake_t role_id);

/**
 * @param client the client created with discord_init()
 * @param code the code of the guild template
 * @ORCA_ret_obj{ret, guild template}
 * @ORCA_return
 */
ORCAcode discord_get_guild_template(struct discord *client,
                                    char *code,
                                    struct discord_guild_template *ret);

/**
 * Creates a template for the guild. Requires the MANAGE_GUILD permission.
 * Returns the created guild template object on success.
 * @param client the client created with discord_init()
 * @param guild_id the guild to create a template of
 * @param params the parameters to create the guild template
 * @ORCA_ret_obj{ret, guild template}
 * @ORCA_return
 */
ORCAcode discord_create_guild_template(
  struct discord *client,
  u64_snowflake_t guild_id,
  struct discord_create_guild_template_params *params,
  struct discord_guild_template *ret);

/**
 * Syncs the template to the guild's current state. Requires the MANAGE_GUILD
 *       permission. Returns the guild template object on success.
 * @param client the client created with discord_init()
 * @param guild_id the guild to sync the template of
 * @param code the identifier of the template to sync
 * @ORCA_ret_obj{ret, guild template}
 * @ORCA_return
 */
ORCAcode discord_sync_guild_template(struct discord *client,
                                     u64_snowflake_t guild_id,
                                     char *code,
                                     struct discord_guild_template *ret);

ORCAcode discord_get_invite(struct discord *client,
                            char *invite_code,
                            struct discord_get_invite_params *params,
                            struct discord_invite *ret);

ORCAcode discord_delete_invite(struct discord *client,
                               char *invite_code,
                               struct discord_invite *ret);

ORCAcode discord_get_user(struct discord *client,
                          u64_snowflake_t user_id,
                          struct discord_user *ret);

ORCAcode discord_modify_current_user(
  struct discord *client,
  struct discord_modify_current_user_params *params,
  struct discord_user *ret);

ORCAcode discord_get_current_user(struct discord *client,
                                  struct discord_user *ret);

ORCAcode discord_get_current_user_guilds(struct discord *client,
                                         struct discord_guild ***ret);

ORCAcode discord_leave_guild(struct discord *client, u64_snowflake_t guild_id);

ORCAcode discord_create_dm(struct discord *client,
                           struct discord_create_dm_params *params,
                           struct discord_channel *ret);

ORCAcode discord_create_group_dm(struct discord *client,
                                 struct discord_create_group_dm_params *params,
                                 struct discord_channel *ret);

/**
 * Returns a list of connection objects.
 * @param client the client created with discord_init()
 * @ORCA_ret_list{ret, connection}
 * @ORCA_return
 */
ORCAcode discord_get_user_connections(struct discord *client,
                                      struct discord_connection ***ret);

/**
 * Returns an array of voice region objects that can be used when setting a
 *       voice or stage channel's rtc_region.
 * @param client the client created with discord_init()
 * @ORCA_ret_list{ret, voice region}
 * @ORCA_return
 */
ORCAcode discord_list_voice_regions(struct discord *client,
                                    struct discord_voice_region ***ret);

/**
 * Create a new webhook. Requires the MANAGE_WEBHOOKS permission. Returns a
 *       webhook object on success.
 * @param client the client created with discord_init()
 * @param channel_id the channel that the webhook belongs to
 * @param params request parameters
 * @ORCA_ret_obj{ret, webhook}
 * @ORCA_return
 */
ORCAcode discord_create_webhook(struct discord *client,
                                u64_snowflake_t channel_id,
                                struct discord_create_webhook_params *params,
                                struct discord_webhook *ret);

/**
 * Returns a list of channel webhook objects. Requires the MANAGE_WEBHOOKS
 *       permission.
 * @param client the client created with discord_init()
 * @param channel_id the channel that the webhooks belongs to
 * @ORCA_ret_list{ret, webhook}
 * @ORCA_return
 */
ORCAcode discord_get_channel_webhooks(struct discord *client,
                                      u64_snowflake_t channel_id,
                                      struct discord_webhook ***ret);

/**
 * Returns a list of guild webhook objects. Requires the MANAGE_WEBHOOKS
 *       permission.
 * @param client the client created with discord_init()
 * @param guild_id the guild that the webhooks belongs to
 * @ORCA_ret_list{ret, webhook}
 * @ORCA_return
 */
ORCAcode discord_get_guild_webhooks(struct discord *client,
                                    u64_snowflake_t guild_id,
                                    struct discord_webhook ***ret);

/**
 * Returns the new webhook object for the given id.
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @ORCA_ret_obj{ret, webhook}
 * @ORCA_return
 */
ORCAcode discord_get_webhook(struct discord *client,
                             u64_snowflake_t webhook_id,
                             struct discord_webhook *ret);

/**
 * Same discord_get_webhook(), except this call does not require authentication
 *       and returns no user in the webhook object
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @ORCA_ret_obj{ret, webhook}
 * @ORCA_return
 */
ORCAcode discord_get_webhook_with_token(struct discord *client,
                                        u64_snowflake_t webhook_id,
                                        const char webhook_token[],
                                        struct discord_webhook *ret);

/**
 * Modify a webhook. Requires the MANAGE_WEBHOOKS permission. Returns the
 *       updated webhook object on success.
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param params request parameters
 * @ORCA_ret_obj{ret, webhook}
 * @ORCA_return
 */
ORCAcode discord_modify_webhook(struct discord *client,
                                u64_snowflake_t webhook_id,
                                struct discord_modify_webhook_params *params,
                                struct discord_webhook *ret);

/**
 * Same discord_modify_webhook(), except this call does not require
 *       authentication and returns no user in the webhook object
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @param params request parameters
 * @ORCA_ret_obj{ret, webhook}
 * @ORCA_return
 */
ORCAcode discord_modify_webhook_with_token(
  struct discord *client,
  u64_snowflake_t webhook_id,
  const char webhook_token[],
  struct discord_modify_webhook_with_token_params *params,
  struct discord_webhook *ret);

/**
 * Delete a webhook permanently. Requires the MANAGE_WEBHOOKS permission.
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @ORCA_return
 */
ORCAcode discord_delete_webhook(struct discord *client,
                                u64_snowflake_t webhook_id);

/**
 * Same discord_delete_webhook(), except this call does not require
 *       authentication.
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @ORCA_return
 */
ORCAcode discord_delete_webhook_with_token(struct discord *client,
                                           u64_snowflake_t webhook_id,
                                           const char webhook_token[]);

/**
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @param params request parameters
 * @ORCA_ret_obj{ret, webhook}
 * @ORCA_return
 */
ORCAcode discord_execute_webhook(struct discord *client,
                                 u64_snowflake_t webhook_id,
                                 const char webhook_token[],
                                 struct discord_execute_webhook_params *params,
                                 struct discord_webhook *ret);

/**
 * Returns a previously-sent webhook message from the same token. Returns a
 *       message object on success.
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @param message_id the message the webhook belongs to
 * @ORCA_ret_obj{ret, message}
 * @ORCA_return
 */
ORCAcode discord_get_webhook_message(struct discord *client,
                                     u64_snowflake_t webhook_id,
                                     const char webhook_token[],
                                     u64_snowflake_t message_id,
                                     struct discord_message *ret);

/**
 * Edits a previously-sent webhook message from the same token. Returns a
 *       message object on success.
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @param message_id the message the webhook belongs to
 * @param params request parameters
 * @ORCA_ret_obj{ret, message}
 * @ORCA_return
 */
ORCAcode discord_edit_webhook_message(
  struct discord *client,
  u64_snowflake_t webhook_id,
  const char webhook_token[],
  u64_snowflake_t message_id,
  struct discord_edit_webhook_message_params *params,
  struct discord_message *ret);

/**
 * Deletes a message that was created by the webhook. Returns a 204 NO CONTENT
 *       response on success.
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @param message_id the message the webhook belongs to
 * @ORCA_return
 */
ORCAcode discord_delete_webhook_message(struct discord *client,
                                        u64_snowflake_t webhook_id,
                                        const char webhook_token[],
                                        u64_snowflake_t message_id);

ORCAcode discord_get_gateway(struct discord *client, struct sized_buffer *ret);

ORCAcode discord_get_gateway_bot(struct discord *client,
                                 struct sized_buffer *ret);

/******************************************************************************
 * Miscellaneous
 ******************************************************************************/

void discord_embed_set_title(struct discord_embed *embed, char format[], ...);
void discord_embed_set_description(struct discord_embed *embed,
                                   char format[],
                                   ...);
void discord_embed_set_url(struct discord_embed *embed, char format[], ...);
void discord_embed_set_thumbnail(struct discord_embed *embed,
                                 char url[],
                                 char proxy_url[],
                                 int height,
                                 int width);
void discord_embed_set_image(struct discord_embed *embed,
                             char url[],
                             char proxy_url[],
                             int height,
                             int width);
void discord_embed_set_video(struct discord_embed *embed,
                             char url[],
                             char proxy_url[],
                             int height,
                             int width);
void discord_embed_set_footer(struct discord_embed *embed,
                              char text[],
                              char icon_url[],
                              char proxy_icon_url[]);
void discord_embed_set_provider(struct discord_embed *embed,
                                char name[],
                                char url[]);
void discord_embed_set_author(struct discord_embed *embed,
                              char name[],
                              char url[],
                              char icon_url[],
                              char proxy_icon_url[]);
void discord_embed_add_field(struct discord_embed *embed,
                             char name[],
                             char value[],
                             bool Inline);

void discord_overwrite_append(
  struct discord_overwrite ***permission_overwrites,
  u64_snowflake_t id,
  int type,
  enum discord_bitwise_permission_flags allow,
  enum discord_bitwise_permission_flags deny);

ORCAcode discord_get_channel_at_pos(struct discord *client,
                                    u64_snowflake_t guild_id,
                                    enum discord_channel_types type,
                                    size_t position,
                                    struct discord_channel *ret);

ORCAcode discord_delete_messages_by_author_id(struct discord *client,
                                              u64_snowflake_t channel_id,
                                              u64_snowflake_t author_id);

ORCAcode discord_disconnect_guild_member(struct discord *client,
                                         u64_snowflake_t guild_id,
                                         u64_snowflake_t user_id,
                                         struct discord_guild_member *ret);

/**
 * @brief Helper function to add presence activities
 *
 * This function is a wrapper over ntl_append2()
 * @see discord_set_presence()
 */
void discord_presence_add_activity(struct discord_presence_status *presence,
                                   struct discord_activity *activity);

/**
 * @brief return value of discord_set_event_scheduler() callback
 *
 * @see discord_set_event_scheduler()
 */
typedef enum discord_event_scheduler {
  /** this event has been handled */
  DISCORD_EVENT_IGNORE,
  /** handle this event in main thread */
  DISCORD_EVENT_MAIN_THREAD,
  /** handle this event in a worker thread */
  DISCORD_EVENT_WORKER_THREAD
} discord_event_scheduler_t;

/**
 * @brief Event Handling Mode callback
 *
 * A very important callback that enables the user with a fine-grained control
 *        of how each event is handled: blocking, non-blocking or ignored
 * @see discord_set_event_scheduler(), @ref discord_gateway_events
 */
typedef enum discord_event_scheduler (*discord_event_scheduler)(
  struct discord *client,
  struct sized_buffer *event_data,
  enum discord_gateway_events event);

/**
 * @brief Provides the user with a fine-grained control of the Discord's
 *       event-loop
 *
 * Allows the user to specify which events should be executed from the
 *       main-thread, in parallel from a worker-thread, or completely ignored.
 *
 * @param client the client created_with discord_init()
 * @param fn the function that will be executed
 * @warning The user is responsible for providing his own locking mechanism to
 *       avoid race-condition on sensitive data.
 * @see @ref discord_event_scheduler, @ref discord_gateway_events
 */
void discord_set_event_scheduler(struct discord *client,
                                 discord_event_scheduler callback);

/**
 * @brief Initialize resources of globals used by discord.h
 *
 * @deprecated use orca_global_init() instead
 */
void discord_global_init();

/**
 * @brief Free resources of globals used by discord.h
 *
 * @deprecated use orca_global_cleanup() instead
 */
void discord_global_cleanup();

#endif /* DISCORD_H */
