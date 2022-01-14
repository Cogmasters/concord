/**
 * @file discord.h
 * @author Cogmasters
 * @brief File containing public functions and datatypes
 *
 * These symbols are organized in a intuitive fashion to be easily
 *        matched to the official Discord API docs
 * @see https://discord.com/developers/docs/intro
 */

#ifndef DISCORD_H
#define DISCORD_H

#include <stdbool.h>

#include "json-actor-boxed.h"
#include "common.h"
#include "logconf.h"

#define DISCORD_API_BASE_URL       "https://discord.com/api/v9"
#define DISCORD_GATEWAY_URL_SUFFIX "?v=9&encoding=json"

/* forward declarations */
struct discord;
/**/

#include "discord-specs.h" /* see specs/api/ */
#include "discord-templates.h"

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

/** @defgroup ConcordDiscordCodes
 * @see @ref ConcordCodes for non-Discord errors
 *  @{ */
/** Received a JSON error message */
#define CCORD_DISCORD_JSON_CODE 1
/** Bad authentication token */
#define CCORD_DISCORD_BAD_AUTH 2
/** Being ratelimited */
#define CCORD_DISCORD_RATELIMIT 3
/** Couldn't establish connection to Discord */
#define CCORD_DISCORD_CONNECTION 4
/** @} ConcordDiscordCodes */

/******************************************************************************
 * Functions specific to the Discord client
 ******************************************************************************/

/**
 * @brief Return the meaning of CCORDcode
 * @note in case of a @ref CCORD_DISCORD_JSON_CODE and if `client` is provided,
 *        a much more descriptive JSON message will be returned instead.
 *
 * @param code the CCORDcode to be explained
 * @param client the client created with discord_init(), NULL for generic error
 *        descriptions
 * @return a string containing the code meaning
 */
const char *discord_strerror(CCORDcode code, struct discord *client);

/**
 * @brief Create a Discord Client handle by its token
 * @see discord_get_logconf() to configure logging behavior
 *
 * @param token the bot token
 * @return the newly created Discord Client handle
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
 *        has its own client instance with unique buffers, url and headers
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

/**
 * @brief Get the client's cached user
 *
 * @param client the client created with discord_init()
 * @warning the returned structure should NOT be modified
 */
const struct discord_user *discord_get_self(struct discord *client);

/**
 * @brief Subscribe to Discord Events
 *
 * @param client the client created with discord_init()
 * @param code the intents opcode, can be set as a bitmask operation
 */
void discord_add_intents(struct discord *client,
                         enum discord_gateway_intents code);
/**
 * @brief Unsubscribe from Discord Events
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
 * @see discord_set_on_command()
 *
 * Example: If @a 'help' is a command and @a '!' prefix is set, the command
 *       will only be validated if @a '!help' is sent
 * @param client the client created with discord_init()
 * @param prefix the prefix that should accompany any command
 */
void discord_set_prefix(struct discord *client, char *prefix);

/**
 * @brief Start a connection to the Discord Gateway
 *
 * @param client the client created with discord_init()
 * @CCORD_return
 */
CCORDcode discord_run(struct discord *client);

/**
 * @brief Block the thread and complete all pending requests
 *
 * @param client the client created with discord_init()
 * @CCORD_return
 */
CCORDcode discord_complete(struct discord *client);

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
 * @see discord_presence_add_activity()
 *
 * @param client the client created with discord_init()
 * @param presence overwrite client's presence with it
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
 * @see logconf_setup(), logconf_set_quiet(), logconf_set_level()
 *
 * @param client the client created with discord_init()
 * @return the client's logging module
 */
struct logconf *discord_get_logconf(struct discord *client);

/******************************************************************************
 * Functions specific to Discord's REST API
 ******************************************************************************/

/**
 * @brief Fetch all of the global commands for your application
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @CCORD_ret_list{ret, application_command}
 * @CCORD_return
 */
CCORDcode discord_get_global_application_commands(
    struct discord *client,
    u64_snowflake_t application_id,
    struct discord_ret_application_commands *ret);

/**
 * @brief Create a new global command
 * @note New global commands will be available in all guilds after 1 hour
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param params request parameters
 * @CCORD_ret_obj{ret, application_command}
 * @CCORD_return
 */
CCORDcode discord_create_global_application_command(
    struct discord *client,
    u64_snowflake_t application_id,
    struct discord_create_global_application_command *params,
    struct discord_ret_application_command *ret);

/**
 * @brief Fetch a global command for your application
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param command_id the registered command id
 * @CCORD_ret_obj{ret, application_command}
 * @CCORD_return
 */
CCORDcode discord_get_global_application_command(
    struct discord *client,
    u64_snowflake_t application_id,
    u64_snowflake_t command_id,
    struct discord_ret_application_command *ret);

/**
 * @brief Edit a global command
 * @note Updates will be available in all guilds after 1 hour
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param command_id the registered command id
 * @param params request parameters
 * @CCORD_ret_obj{ret, application_command}
 * @CCORD_return
 */
CCORDcode discord_edit_global_application_command(
    struct discord *client,
    u64_snowflake_t application_id,
    u64_snowflake_t command_id,
    struct discord_edit_global_application_command *params,
    struct discord_ret_application_command *ret);

/**
 * @brief Deletes a global command
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param command_id the registered command id
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_global_application_command(
    struct discord *client,
    u64_snowflake_t application_id,
    u64_snowflake_t command_id,
    struct discord_ret *ret);

/**
 * @brief Overwrite existing global application commands
 * @note Updates will be available in all guilds after 1 hour
 * @warning Will overwrite all types of application commands: slash
 *        commands, user commands, and message commands
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param params the request parameters, a list of application commands
 * @CCORD_ret_list{ret, application_command}
 * @CCORD_return
 */
CCORDcode discord_bulk_overwrite_global_application_command(
    struct discord *client,
    u64_snowflake_t application_id,
    struct discord_application_command **params,
    struct discord_ret_application_commands *ret);

/**
 * @brief Fetch all of the guild commands of a given guild
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the commands are located
 * @CCORD_ret_list{ret, application_command}
 * @CCORD_return
 */
CCORDcode discord_get_guild_application_commands(
    struct discord *client,
    u64_snowflake_t application_id,
    u64_snowflake_t guild_id,
    struct discord_ret_application_commands *ret);

/**
 * @brief Create a new guild command
 * @note Commands will be available in the guild immediately
 * @note Will overwrite any existing guild command with the same name
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the command is located
 * @param params request parameters
 * @CCORD_ret_obj{ret, application_command}
 * @CCORD_return
 */
CCORDcode discord_create_guild_application_command(
    struct discord *client,
    u64_snowflake_t application_id,
    u64_snowflake_t guild_id,
    struct discord_create_guild_application_command *params,
    struct discord_ret_application_command *ret);

/**
 * @brief Fetch a guild command for your application
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the command is located
 * @param command_id the registered command id
 * @CCORD_ret_obj{ret, application_command}
 * @CCORD_return
 */
CCORDcode discord_get_guild_application_command(
    struct discord *client,
    u64_snowflake_t application_id,
    u64_snowflake_t guild_id,
    u64_snowflake_t command_id,
    struct discord_ret_application_command *ret);

/**
 * @brief Edit a guild command
 * @note Updates for guild commands will be available immediately
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the command is located
 * @param command_id the registered command id
 * @param params request parameters
 * @CCORD_ret_obj{ret, application_command}
 * @CCORD_return
 */
CCORDcode discord_edit_guild_application_command(
    struct discord *client,
    u64_snowflake_t application_id,
    u64_snowflake_t guild_id,
    u64_snowflake_t command_id,
    struct discord_edit_guild_application_command *params,
    struct discord_ret_application_command *ret);

/**
 * @brief Deletes a guild command
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the command is located
 * @param command_id the registered command id
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_guild_application_command(
    struct discord *client,
    u64_snowflake_t application_id,
    u64_snowflake_t guild_id,
    u64_snowflake_t command_id,
    struct discord_ret *ret);

/**
 * @brief Overwrite existing guild application commands
 * @warning This will overwrite all types of application commands: slash
 *        commands, user commands, and message commands
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the commands are located
 * @param params the request parameters, a list of application commands
 * @CCORD_ret_list{ret, application_command}
 * @CCORD_return
 */
CCORDcode discord_bulk_overwrite_guild_application_command(
    struct discord *client,
    u64_snowflake_t application_id,
    u64_snowflake_t guild_id,
    struct discord_application_command **params,
    struct discord_ret_application_commands *ret);

/**
 * @brief Fetches command permissions for all commands in a given guild
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the commands are located
 * @CCORD_ret_list{ret, guild_application_command_permissions}
 * @CCORD_return
 */
CCORDcode discord_get_guild_application_command_permissions(
    struct discord *client,
    u64_snowflake_t application_id,
    u64_snowflake_t guild_id,
    struct discord_ret_guild_application_command_permissionss *ret);

/**
 * @brief Fetches command permissions for a specific command in a given guild
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the command is located
 * @param command_id the registered command id
 * @CCORD_ret_obj{ret, application_command_permissions}
 * @CCORD_return
 */
CCORDcode discord_get_application_command_permissions(
    struct discord *client,
    u64_snowflake_t application_id,
    u64_snowflake_t guild_id,
    u64_snowflake_t command_id,
    struct discord_ret_application_command_permissions *ret);

/**
 * @brief Edits command permissions for a specific command in a given guild
 * @note You can only add up to 10 permission overwrites for a command
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the commands are located
 * @param command_id the registered command id
 * @param params the request parameters
 * @CCORD_ret_obj{ret, application_command_permissions}
 * @CCORD_return
 */
CCORDcode discord_edit_application_command_permissions(
    struct discord *client,
    u64_snowflake_t application_id,
    u64_snowflake_t guild_id,
    u64_snowflake_t command_id,
    struct discord_edit_application_command_permissions *params,
    struct discord_ret_application_command_permissions *ret);

/**
 * @brief Batch edits permissions for all commands in a guild
 * @note You can only add up to 10 permission overwrites for a command
 * @warning This will overwrite all types of application commands: slash
 *       commands, user commands, and message commands
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the parent application
 * @param guild_id the guild where the commands are located
 * @param params the request parameters, a list of guild application commands
 *       permissions
 * @CCORD_ret_list{ret, guild_application_command_permissions}
 * @CCORD_return
 */
CCORDcode discord_batch_edit_application_command_permissions(
    struct discord *client,
    u64_snowflake_t application_id,
    u64_snowflake_t guild_id,
    struct discord_guild_application_command_permissions **params,
    struct discord_ret_guild_application_command_permissionss *ret);

/**
 * @brief Create a response to an Interaction from the gateway
 *
 * @param client the client created with discord_init()
 * @param interaction_id the unique id of the interaction
 * @param interaction_token the unique token of the interaction
 * @param params the request parameters
 * @CCORD_ret_obj{ret, interaction_response}
 * @CCORD_return
 */
CCORDcode discord_create_interaction_response(
    struct discord *client,
    u64_snowflake_t interaction_id,
    const char interaction_token[],
    struct discord_interaction_response *params,
    struct discord_ret_interaction_response *ret);

/**
 * @brief Get the initial Interaction response
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the application
 * @param interaction_token the unique token of the interaction
 * @CCORD_ret_obj{ret, interaction_response}
 * @CCORD_return
 */
CCORDcode discord_get_original_interaction_response(
    struct discord *client,
    u64_snowflake_t application_id,
    const char interaction_token[],
    struct discord_ret_interaction_response *ret);

/**
 * @brief Edit the initial Interaction response
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the application
 * @param interaction_token the unique token of the interaction
 * @param params request parameters
 * @CCORD_ret_obj{ret, interaction_response}
 * @CCORD_return
 */
CCORDcode discord_edit_original_interaction_response(
    struct discord *client,
    u64_snowflake_t application_id,
    const char interaction_token[],
    struct discord_edit_original_interaction_response *params,
    struct discord_ret_interaction_response *ret);

/**
 * @brief Delete the initial Interaction response
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the application
 * @param interaction_token the unique token of the interaction
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_original_interaction_response(
    struct discord *client,
    u64_snowflake_t application_id,
    const char interaction_token[],
    struct discord_ret *ret);

/**
 * @brief Create a followup message for an Interaction
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the application
 * @param interaction_token the unique token of the interaction
 * @param params request parameters
 * @CCORD_ret_obj{ret, webhook}
 * @CCORD_return
 */
CCORDcode discord_create_followup_message(
    struct discord *client,
    u64_snowflake_t application_id,
    const char interaction_token[],
    struct discord_create_followup_message *params,
    struct discord_ret_webhook *ret);

/**
 * @brief Get a followup message for an interaction
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the application
 * @param interaction_token the unique token of the interaction
 * @param message_id the unique id of the message
 * @CCORD_ret_obj{ret, message}
 * @CCORD_return
 */
CCORDcode discord_get_followup_message(struct discord *client,
                                       u64_snowflake_t application_id,
                                       const char interaction_token[],
                                       u64_snowflake_t message_id,
                                       struct discord_ret_message *ret);

/**
 * @brief Edits a followup message for an interaction
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the application
 * @param interaction_token the unique token of the interaction
 * @param message_id the unique id of the message
 * @param params request parameters
 * @CCORD_ret_obj{ret, message}
 * @CCORD_return
 */
CCORDcode discord_edit_followup_message(
    struct discord *client,
    u64_snowflake_t application_id,
    const char interaction_token[],
    u64_snowflake_t message_id,
    struct discord_edit_followup_message *params,
    struct discord_ret_message *ret);

/**
 * @brief Edits a followup message for an interaction
 *
 * @param client the client created with discord_init()
 * @param application_id the unique id of the application
 * @param interaction_token the unique token of the interaction
 * @param message_id the unique id of the message
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_followup_message(struct discord *client,
                                          u64_snowflake_t application_id,
                                          const char interaction_token[],
                                          u64_snowflake_t message_id,
                                          struct discord_ret *ret);

/**
 * @brief Get audit log for a given guild
 *
 * @note Requires the 'VIEW_AUDIT_LOG' permission
 * @param client the client created with discord_init()
 * @param guild_id the guild to retrieve the audit log from
 * @param params request parameters
 * @CCORD_ret_obj{ret, audit_log}
 * @CCORD_return
 */
CCORDcode discord_get_guild_audit_log(
    struct discord *client,
    u64_snowflake_t guild_id,
    struct discord_get_guild_audit_log *params,
    struct discord_ret_audit_log *ret);

/**
 * @brief Get channel from given id
 * @note If the channel is a thread, a thread member object is included in the
 * returned result
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel to be retrieved
 * @CCORD_ret_obj{ret, channel}
 * @CCORD_return
 */
CCORDcode discord_get_channel(struct discord *client,
                              u64_snowflake_t channel_id,
                              struct discord_ret_channel *ret);

/**
 * @brief Update a channel's settings
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel to be modified
 * @param params request parameters
 * @CCORD_ret_obj{ret, channel}
 * @CCORD_return
 */
CCORDcode discord_modify_channel(struct discord *client,
                                 u64_snowflake_t channel_id,
                                 struct discord_modify_channel *params,
                                 struct discord_ret_channel *ret);

/**
 * @brief Delete a channel, or close a private message
 * @note Requires the MANAGE_CHANNELS permission for the guild, or
 *        MANAGE_THREADS if the channel is a thread
 * @note Deleting a category does not delete its child channels; they will have
 *        their parent_id removed and a `Channel Update Gateway` event will
 * fire for each of them
 * @note Fires a `Channel Delete` event (or `Thread Delete` if the channel
 *       was a thread)
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel to be deleted
 * @CCORD_ret_obj{ret, channel}
 * @CCORD_return
 */
CCORDcode discord_delete_channel(struct discord *client,
                                 u64_snowflake_t channel_id,
                                 struct discord_ret_channel *ret);

/**
 * @brief Get messages for a given channel
 * @note If operating on a guild channel, this endpoint requires the
 *        VIEW_CHANNEL permission to be present on the current user
 * @note If the current user is missing the READ_MESSAGE_HISTORY permission
 *       in the channel then this will return no messages (since they cannot
 *        read the message history)
 * @note The before, after, and around keys are mutually exclusive, only one
 *       may be passed at a time
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel to get messages from
 * @param params request parameters
 * @CCORD_ret_list{ret, message}
 * @CCORD_return
 */
CCORDcode discord_get_channel_messages(
    struct discord *client,
    u64_snowflake_t channel_id,
    struct discord_get_channel_messages *params,
    struct discord_ret_messages *ret);

/**
 * @brief Get a specific message in the channel
 * @note If operating on a guild channel, this endpoint requires the
 * 'READ_MESSAGE_HISTORY' permission to be present on the current user
 * @param client the client created with discord_init()
 * @param channel_id the channel where the message resides
 * @param message_id the message itself
 * @CCORD_ret_obj{ret, message}
 * @CCORD_return
 */
CCORDcode discord_get_channel_message(struct discord *client,
                                      u64_snowflake_t channel_id,
                                      u64_snowflake_t message_id,
                                      struct discord_ret_message *ret);

/**
 * @brief Post a message to a guild text or DM channel
 * @note Fires a `Message Create` event
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel to send the message at
 * @param params request parameters
 * @CCORD_ret_obj{ret, message}
 * @CCORD_return
 */
CCORDcode discord_create_message(struct discord *client,
                                 u64_snowflake_t channel_id,
                                 struct discord_create_message *params,
                                 struct discord_ret_message *ret);

/**
 * @brief Crosspost a message in a News Channel to following channels
 * @note This endpoint requires the 'SEND_MESSAGES' permission, if the current
 *        user sent the message, or additionally the 'MANAGE_MESSAGES'
 *        permission, for all other messages, to be present for the current
 *        user
 *
 * @param client the client created with discord_init()
 * @param channel_id the news channel that will crosspost
 * @param message_id the message that will crospost
 * @CCORD_ret_obj{ret, message}
 * @CCORD_return
 */
CCORDcode discord_crosspost_message(struct discord *client,
                                    u64_snowflake_t channel_id,
                                    u64_snowflake_t message_id,
                                    struct discord_ret_message *ret);

/**
 * @brief Create a reaction for the message
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message to receive a reaction
 * @param emoji_id the emoji id (leave as 0 if not a custom emoji)
 * @param emoji_name the emoji name
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_create_reaction(struct discord *client,
                                  u64_snowflake_t channel_id,
                                  u64_snowflake_t message_id,
                                  u64_snowflake_t emoji_id,
                                  const char emoji_name[],
                                  struct discord_ret *ret);

/**
 * @brief Delete a reaction the current user has made for the message
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message to have a reaction deleted
 * @param emoji_id the emoji id (leave as 0 if not a custom emoji)
 * @param emoji_name the emoji name
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_own_reaction(struct discord *client,
                                      u64_snowflake_t channel_id,
                                      u64_snowflake_t message_id,
                                      u64_snowflake_t emoji_id,
                                      const char emoji_name[],
                                      struct discord_ret *ret);

/**
 * @brief Deletes another user's reaction
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message to have a reaction deleted
 * @param user_id the user the reaction belongs to
 * @param emoji_id the emoji id (leave as 0 if not a custom emoji)
 * @param emoji_name the emoji name
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_user_reaction(struct discord *client,
                                       u64_snowflake_t channel_id,
                                       u64_snowflake_t message_id,
                                       u64_snowflake_t user_id,
                                       u64_snowflake_t emoji_id,
                                       const char emoji_name[],
                                       struct discord_ret *ret);

/**
 * @brief Get a list of users that reacted with given emoji
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message reacted to
 * @param emoji_id the emoji id (leave as 0 if not a custom emoji)
 * @param emoji_name the emoji name
 * @param params request parameters
 * @CCORD_ret_list{ret, user}
 * @CCORD_return
 */
CCORDcode discord_get_reactions(struct discord *client,
                                u64_snowflake_t channel_id,
                                u64_snowflake_t message_id,
                                u64_snowflake_t emoji_id,
                                const char emoji_name[],
                                struct discord_get_reactions *params,
                                struct discord_ret_users *ret);

/**
 * @brief Deletes all reactions from message
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message that will be purged of reactions
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_all_reactions(struct discord *client,
                                       u64_snowflake_t channel_id,
                                       u64_snowflake_t message_id,
                                       struct discord_ret *ret);

/**
 * @brief Deletes all the reactions for a given emoji on message
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message that will be purged of reactions from
 *       particular emoji
 * @param emoji_id the emoji id (leave as 0 if not a custom emoji)
 * @param emoji_name the emoji name
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_all_reactions_for_emoji(struct discord *client,
                                                 u64_snowflake_t channel_id,
                                                 u64_snowflake_t message_id,
                                                 u64_snowflake_t emoji_id,
                                                 const char emoji_name[],
                                                 struct discord_ret *ret);

/**
 * @brief Edit a previously sent message
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message that will be purged of reactions from
 *       particular emoji
 * @param params request parameters
 * @CCORD_ret_obj{ret, message}
 * @CCORD_return
 */
CCORDcode discord_edit_message(struct discord *client,
                               u64_snowflake_t channel_id,
                               u64_snowflake_t message_id,
                               struct discord_edit_message *params,
                               struct discord_ret_message *ret);

/**
 * @brief Delete a message
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param message_id the message that will be purged of reactions from
 *       particular emoji
 * @CCORD_return
 */
CCORDcode discord_delete_message(struct discord *client,
                                 u64_snowflake_t channel_id,
                                 u64_snowflake_t message_id,
                                 struct discord_ret *ret);

/**
 * @brief Delete multiple messages in a single request
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param messages the null-terminated list of messages to be deleted
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_bulk_delete_messages(struct discord *client,
                                       u64_snowflake_t channel_id,
                                       u64_snowflake_t **messages,
                                       struct discord_ret *ret);

/**
 * @brief Edit the channel permission overwrites for a user or role in a
 *        channel
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param overwrite_id
 * @param params request parameters
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_edit_channel_permissions(
    struct discord *client,
    u64_snowflake_t channel_id,
    u64_snowflake_t overwrite_id,
    struct discord_edit_channel_permissions *params,
    struct discord_ret *ret);

/**
 * @brief Get invites (with invite metadata) for the channel
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @CCORD_ret_list{ret, invite}
 * @CCORD_return
 */
CCORDcode discord_get_channel_invites(struct discord *client,
                                      u64_snowflake_t channel_id,
                                      struct discord_ret_invites *ret);

/**
 * @brief Create a new invite for the channel
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel that the message belongs to
 * @param params request parameters
 * @CCORD_ret_obj{ret, invite}
 * @CCORD_return
 */
CCORDcode discord_create_channel_invite(
    struct discord *client,
    u64_snowflake_t channel_id,
    struct discord_create_channel_invite *params,
    struct discord_ret_invite *ret);

/**
 * @brief Delete a channel permission overwrite for a user or role in a
 *        channel
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel to the permission deleted
 * @param overwrite_id the id of the overwritten permission
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_channel_permission(struct discord *client,
                                            u64_snowflake_t channel_id,
                                            u64_snowflake_t overwrite_id,
                                            struct discord_ret *ret);

/**
 * @brief Post a typing indicator for the specified channel
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel to post the typing indicator to
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_trigger_typing_indicator(struct discord *client,
                                           u64_snowflake_t channel_id,
                                           struct discord_ret *ret);

/**
 * @brief Follow a News Channel to send messages to a target channel
 * @note Requires MANAGE_WEBHOOKS permission in the target channel
 *        MANAGE_WEBHOOKS permission in the target channel
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel to post the typing indicator to
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_follow_news_channel(
    struct discord *client,
    u64_snowflake_t channel_id,
    struct discord_follow_news_channel *params,
    struct discord_ret *ret);

CCORDcode discord_get_pinned_messages(struct discord *client,
                                      u64_snowflake_t channel_id,
                                      struct discord_ret *ret);

/**
 * @brief Pin a message to a channel
 *
 * @param client the client created with discord_init()
 * @param channel_id channel to pin the message on
 * @param message_id message to be pinned
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_pin_message(struct discord *client,
                              u64_snowflake_t channel_id,
                              u64_snowflake_t message_id,
                              struct discord_ret *ret);

/**
 * @brief Unpin a message from a channel
 *
 * @param client the client created with discord_init()
 * @param channel_id channel for the message to be unpinned
 * @param message_id message to be unpinned
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_unpin_message(struct discord *client,
                                u64_snowflake_t channel_id,
                                u64_snowflake_t message_id,
                                struct discord_ret *ret);

/**
 * @brief Adds a recipient to a Group DM using their access token
 *
 * @param client the client created with discord_init()
 * @param channel_id group to add the user in
 * @param user_id user to be added
 * @param params request parameters
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_group_dm_add_recipient(
    struct discord *client,
    u64_snowflake_t channel_id,
    u64_snowflake_t user_id,
    struct discord_group_dm_add_recipient *params,
    struct discord_ret *ret);

/**
 * @brief Removes a recipient from a Group DM
 *
 * @param client the client created with discord_init()
 * @param channel_id channel for the user to be removed from
 * @param user_id user to be removed
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_group_dm_remove_recipient(struct discord *client,
                                            u64_snowflake_t channel_id,
                                            u64_snowflake_t user_id,
                                            struct discord_ret *ret);

/**
 * @brief Creates a new thread from an existing message
 * @note Fires a `Thread Create` event
 *
 * @param client the client created with discord_init()
 * @param channel_id channel to start a thread on
 * @param message_id message to start a thread from
 * @param params request parameters
 * @CCORD_ret_obj{ret, channel}
 * @CCORD_return
 */
CCORDcode discord_start_thread_with_message(
    struct discord *client,
    u64_snowflake_t channel_id,
    u64_snowflake_t message_id,
    struct discord_start_thread_with_message *params,
    struct discord_ret_channel *ret);

/**
 * @brief Creates a new thread that is not connected to an existing message
 * @note Fires a `Thread Create` event
 *
 * @param client the client created with discord_init()
 * @param channel_id channel to start a thread on
 * @param params request parameters
 * @CCORD_ret_obj{ret, channel}
 * @CCORD_return
 */
CCORDcode discord_start_thread_without_message(
    struct discord *client,
    u64_snowflake_t channel_id,
    struct discord_start_thread_without_message *params,
    struct discord_ret_channel *ret);

/**
 * @brief Adds the current user to an un-archived thread
 * @note Fires a `Thread Members Update` event
 *
 * @param client the client created with discord_init()
 * @param channel_id the thread to be joined
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_join_thread(struct discord *client,
                              u64_snowflake_t channel_id,
                              struct discord_ret *ret);

/**
 * @brief Adds another member to an un-archived thread
 * @note Fires a `Thread Members Update` event
 *
 * @param client the client created with discord_init()
 * @param channel_id the thread to be joined
 * @param user_id user to be added to thread
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_add_thread_member(struct discord *client,
                                    u64_snowflake_t channel_id,
                                    u64_snowflake_t user_id,
                                    struct discord_ret *ret);

/**
 * @brief Removes the current user from a un-archived thread
 * @note Fires a `Thread Members Update` event
 *
 * @param client the client created with discord_init()
 * @param channel_id the thread to be removed from
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_leave_thread(struct discord *client,
                               u64_snowflake_t channel_id,
                               struct discord_ret *ret);

/**
 * @brief Removes another member from a un-archived thread
 * @note Fires a `Thread Members Update` event
 * @note Requires `MANAGE_THREADS` permission
 *
 * @param client the client created with discord_init()
 * @param channel_id the thread to be removed from
 * @param user_id user to be removed
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_remove_thread_member(struct discord *client,
                                       u64_snowflake_t channel_id,
                                       u64_snowflake_t user_id,
                                       struct discord_ret *ret);

/**
 * @brief Get members from a given thread channel
 * @note Fires a `Thread Members Update` event
 * @note Requires `MANAGE_THREADS` permission
 *
 * @param client the client created with discord_init()
 * @param channel_id the thread to be joined
 * @CCORD_ret_list{ret, thread_member}
 * @CCORD_return
 */
CCORDcode discord_list_thread_members(struct discord *client,
                                      u64_snowflake_t channel_id,
                                      struct discord_ret_thread_members *ret);

/**
 * @todo replace with
 * https://discord.com/developers/docs/resources/guild#list-active-threads
 * @deprecated Discord will deprecate this in V10
 * @brief Get all active threads in a given channel
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel to be searched for threads
 * @CCORD_ret_obj{ret, thread_response_body}
 * @CCORD_return
 */
CCORDcode discord_list_active_threads(
    struct discord *client,
    u64_snowflake_t channel_id,
    struct discord_ret_thread_response_body *ret);

/**
 * @brief Get public archived threads in a given channel
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel to be searched for threads
 * @param before return threads before this timestamp
 * @param limit maximum number of threads to return
 * @CCORD_ret_obj{ret, thread_response_body}
 * @CCORD_return
 */
CCORDcode discord_list_public_archived_threads(
    struct discord *client,
    u64_snowflake_t channel_id,
    u64_unix_ms_t before,
    int limit,
    struct discord_ret_thread_response_body *ret);

/**
 * @brief Get private archived threads in a given channel
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel to be searched for threads
 * @param before return threads before this timestamp
 * @param limit maximum number of threads to return
 * @CCORD_ret_obj{ret, thread_response_body}
 * @CCORD_return
 */
CCORDcode discord_list_private_archived_threads(
    struct discord *client,
    u64_snowflake_t channel_id,
    u64_unix_ms_t before,
    int limit,
    struct discord_ret_thread_response_body *ret);

/**
 * @brief Get private archived threads that current user has joined
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel to be searched for threads
 * @param before return threads before this timestamp
 * @param limit maximum number of threads to return
 * @CCORD_ret_obj{ret, thread_response_body}
 * @CCORD_return
 */
CCORDcode discord_list_joined_private_archived_threads(
    struct discord *client,
    u64_snowflake_t channel_id,
    u64_unix_ms_t before,
    int limit,
    struct discord_ret_thread_response_body *ret);

/**
 * @brief Get emojis of a given guild
 *
 * @param client the client created with discord_init()
 * @param guild_id guild to get emojis from
 * @CCORD_ret_list{ret, emoji}
 * @CCORD_return
 */
CCORDcode discord_list_guild_emojis(struct discord *client,
                                    u64_snowflake_t guild_id,
                                    struct discord_ret_emojis *ret);

/**
 * @brief Get a specific emoji from a guild
 *
 * @param client the client created with discord_init()
 * @param guild_id guild the emoji belongs to
 * @param emoji_id the emoji to be fetched
 * @CCORD_ret_obj{ret, emoji}
 * @CCORD_return
 */
CCORDcode discord_get_guild_emoji(struct discord *client,
                                  u64_snowflake_t guild_id,
                                  u64_snowflake_t emoji_id,
                                  struct discord_ret_emoji *ret);

/**
 * @brief Create a new emoji for the guild
 * @note Fires a `Guild Emojis Update` event
 *
 * @param client the client created with discord_init()
 * @param guild_id guild to add the new emoji to
 * @param params request parameters
 * @CCORD_ret_obj{ret, emoji}
 * @CCORD_return
 */
CCORDcode discord_create_guild_emoji(struct discord *client,
                                     u64_snowflake_t guild_id,
                                     struct discord_create_guild_emoji *params,
                                     struct discord_ret_emoji *ret);

/**
 * @brief Modify the given emoji
 * @note Fires a `Guild Emojis Update` event
 *
 * @param client the client created with discord_init()
 * @param guild_id guild the emoji belongs to
 * @param emoji_id the emoji to be modified
 * @param params request parameters
 * @CCORD_ret_obj{ret, emoji}
 * @CCORD_return
 */
CCORDcode discord_modify_guild_emoji(struct discord *client,
                                     u64_snowflake_t guild_id,
                                     u64_snowflake_t emoji_id,
                                     struct discord_modify_guild_emoji *params,
                                     struct discord_ret_emoji *ret);

/**
 * @brief Deletes the given emoji
 * @note Fires a `Guild Emojis Update` event
 *
 * @param client the client created with discord_init()
 * @param guild_id guild the emoji belongs to
 * @param emoji_id the emoji to be deleted
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_guild_emoji(struct discord *client,
                                     u64_snowflake_t guild_id,
                                     u64_snowflake_t emoji_id,
                                     struct discord_ret *ret);

/**
 * @brief Create a new guild
 * @note Fires a `Guild Create` event
 *
 * @param client the client created with discord_init()
 * @param params request parameters
 * @CCORD_ret_obj{ret, guild}
 * @CCORD_return
 */
CCORDcode discord_create_guild(struct discord *client,
                               struct discord_create_guild *params,
                               struct discord_ret_guild *ret);

/**
 * @brief Get the guild with given id
 * @note If with_counts is set to true, this endpoint will also return
 *        approximate_member_count and approximate_presence_count for the
 *        guild
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to retrieve
 * @CCORD_ret_obj{ret, guild}
 * @CCORD_return
 */
CCORDcode discord_get_guild(struct discord *client,
                            u64_snowflake_t guild_id,
                            struct discord_ret_guild *ret);

/**
 * @brief Get the preview for the given guild
 * @note If the user is not in the guild, then the guild must be lurkable
 *
 * @param client the client created with discord_init()
 * @param guild_id guild to get preview from
 * @CCORD_ret_obj{ret, guild_preview}
 * @CCORD_return
 */
CCORDcode discord_get_guild_preview(struct discord *client,
                                    u64_snowflake_t guild_id,
                                    struct discord_ret_guild_preview *ret);

/**
 * @brief Modify a guild's settings
 * @note Requires the MANAGE_GUILD permission
 * @note Fires a `Guild Update` event
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to modify
 * @param params request parameters
 * @CCORD_ret_obj{ret, guild}
 * @CCORD_return
 */
CCORDcode discord_modify_guild(struct discord *client,
                               u64_snowflake_t guild_id,
                               struct discord_modify_guild *params,
                               struct discord_ret_guild *ret);

/**
 * @brief Delete a guild permanently, user must be owner
 * @note Fires a `Guild Delete` event
 *
 * @param client the client created with discord_init()
 * @param guild_id id of guild to delete
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_guild(struct discord *client,
                               u64_snowflake_t guild_id,
                               struct discord_ret *ret);

/**
 * @brief Fetch channels from given guild. Does not include threads
 *
 * @param client the client created with discord_init()
 * @param guild_id id of guild to fetch channels from
 * @CCORD_ret_list{ret, channel}
 * @CCORD_return
 */
CCORDcode discord_get_guild_channels(struct discord *client,
                                     u64_snowflake_t guild_id,
                                     struct discord_ret_channels *ret);

/**
 * @brief Create a new guild channel
 * @note Requires the MANAGE_CHANNELS permission
 * @note If setting permission overwrites, only permissions your
 *       bot has in the guild can be allowed/denied. Setting MANAGE_ROLES
 *       permission in channels is only possible for guild administrators
 * @note Fires a `Channel Create` event
 *
 * @param client the client created with discord_init()
 * @param guild_id id of the guild to create a channel at
 * @param params request parameters
 * @CCORD_ret_obj{ret, channel}
 * @CCORD_return
 */
CCORDcode discord_create_guild_channel(
    struct discord *client,
    u64_snowflake_t guild_id,
    struct discord_create_guild_channel *params,
    struct discord_ret_channel *ret);

/**
 * @brief Modify guild channel positions
 * @note Requires MANAGE_CHANNELS permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to change the positions of the
 *       channels in
 * @param params request parameters
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_modify_guild_channel_positions(
    struct discord *client,
    u64_snowflake_t guild_id,
    struct discord_modify_guild_channel_positions **params,
    struct discord_ret *ret);

/**
 * @brief Get guild member of a guild from given user id
 *
 * @param client the client created with discord_init()
 * @param guild_id guild the member belongs to
 * @param user_id unique user id of member
 * @CCORD_ret_obj{ret, guild_member}
 * @CCORD_return
 */
CCORDcode discord_get_guild_member(struct discord *client,
                                   u64_snowflake_t guild_id,
                                   u64_snowflake_t user_id,
                                   struct discord_ret_guild_member *ret);

/**
 * @brief Get guild members of a guild
 *
 * @param client the client created with discord_init()
 * @param guild_id guild the members belongs to
 * @param request parameters
 * @CCORD_ret_list{ret, guild_member}
 * @CCORD_return
 */
CCORDcode discord_list_guild_members(struct discord *client,
                                     u64_snowflake_t guild_id,
                                     struct discord_list_guild_members *params,
                                     struct discord_ret_guild_members *ret);

/**
 * @brief Get guild members whose username or nickname starts with a provided
 *        string
 *
 * @param client the client created with discord_init()
 * @param guild_id guild the members belongs to
 * @param request parameters
 * @CCORD_ret_list{ret, guild_member}
 * @CCORD_return
 */
CCORDcode discord_search_guild_members(
    struct discord *client,
    u64_snowflake_t guild_id,
    struct discord_search_guild_members *params,
    struct discord_ret_guild_members *ret);

/**
 * @brief Adds a user to the guild
 * @note Requires valid oauth2 access token for the user with `guilds.join`
 *       scope
 * @note Fires a `Guild Member Add` event
 * @note The bot must be a member of the guild with CREATE_INSTANT_INVITE
 *       permission
 *
 * @param client the client created with discord_init()
 * @param guild_id guild to add the member to
 * @param user_id the user to be added
 * @param request parameters
 * @CCORD_ret_obj{ret, guild_member}
 * @CCORD_return
 */
CCORDcode discord_add_guild_member(struct discord *client,
                                   u64_snowflake_t guild_id,
                                   u64_snowflake_t user_id,
                                   struct discord_add_guild_member *params,
                                   struct discord_ret_guild_member *ret);

/**
 * @brief Modify retibutes of a guild member
 * @note Fires a `Guild Member Update` event
 * @see discord_disconnect_guild_member()
 *
 * @param client the client created with discord_init()
 * @param guild_id guild the member belongs to
 * @param user_id the user id of member
 * @param request parameters
 * @CCORD_ret_obj{ret, guild_member}
 * @CCORD_return
 */
CCORDcode discord_modify_guild_member(
    struct discord *client,
    u64_snowflake_t guild_id,
    u64_snowflake_t user_id,
    struct discord_modify_guild_member *params,
    struct discord_ret_guild_member *ret);

/**
 * @brief Modifies the current member in the guild
 * @note Fires a `Guild Member Update` event
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild where the member exists
 * @param params request parameters
 * @CCORD_ret_obj{ret, guild_member}
 * @CCORD_return
 */
CCORDcode discord_modify_current_member(
    struct discord *client,
    u64_snowflake_t guild_id,
    struct discord_modify_current_member *params,
    struct discord_ret_guild_member *ret);

/**
 * @deprecated use discord_modify_current_member() instead
 * @brief Modify the nickname of the current user in a guild
 * @note Fires a `Guild Member Update` event
 *
 * @param client the client created with discord_init()
 * @param guild_id guild the member belongs to
 * @param params request parameters
 * @CCORD_ret_obj{ret, guild_member}
 * @CCORD_return
 */
CCORDcode discord_modify_current_user_nick(
    struct discord *client,
    u64_snowflake_t guild_id,
    struct discord_modify_current_user_nick *params,
    struct discord_ret_guild_member *ret);

/**
 * @brief Adds a role to a guild member
 * @note Fires a `Guild Member Update` event
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild where the member exists
 * @param user_id the unique id of the user
 * @param role_id the unique id of the role to be added
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_add_guild_member_role(struct discord *client,
                                        u64_snowflake_t guild_id,
                                        u64_snowflake_t user_id,
                                        u64_snowflake_t role_id,
                                        struct discord_ret *ret);

/**
 * @brief Removes a role from a guild member
 * @note Requires the MANAGE_ROLES permission
 * @note Fires a `Guild Member Update` event
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild where the member exists
 * @param user_id the unique id of the user
 * @param role_id the unique id of the role to be removed
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_remove_guild_member_role(struct discord *client,
                                           u64_snowflake_t guild_id,
                                           u64_snowflake_t user_id,
                                           u64_snowflake_t role_id,
                                           struct discord_ret *ret);

/**
 * @brief Remove a member from a guild
 * @note Requires the KICK_MEMBERS permission
 * @note Fires a `Guild Member Update` event
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild to remove the member from
 * @param user_id the user to be removed
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_remove_guild_member(struct discord *client,
                                      u64_snowflake_t guild_id,
                                      u64_snowflake_t user_id,
                                      struct discord_ret *ret);

/**
 * @brief Fetch banned users for given guild
 * @note Requires the BAN_MEMBERS permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild to get the list from
 * @CCORD_ret_list{ret, ban}
 * @CCORD_return
 */
CCORDcode discord_get_guild_bans(struct discord *client,
                                 u64_snowflake_t guild_id,
                                 struct discord_ret_bans *ret);

/**
 * @brief Fetch banned user from given guild
 * @note Requires the BAN_MEMBERS permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild to return the ban from
 * @param user_id the user that is banned
 * @CCORD_ret_obj{ret, ban}
 * @CCORD_return
 */
CCORDcode discord_get_guild_ban(struct discord *client,
                                u64_snowflake_t guild_id,
                                u64_snowflake_t user_id,
                                struct discord_ret_ban *ret);

/**
 * @brief Bans user from a given guild
 * @note Requires the BAN_MEMBERS permission
 * @note Fires a `Guild Ban Add` event
 *
 * @param client the client created with discord_init()
 * @param guild_id guild the user belongs to
 * @param user_id the user to be banned
 * @param params request parameters
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_create_guild_ban(struct discord *client,
                                   u64_snowflake_t guild_id,
                                   u64_snowflake_t user_id,
                                   struct discord_create_guild_ban *params,
                                   struct discord_ret *ret);

/**
 * @brief Remove the ban for a user
 * @note Requires the BAN_MEMBERS permission
 * @note Fires a `Guild Ban Remove` event
 *
 * @param client the client created with discord_init()
 * @param guild_id guild the user belonged to
 * @param user_id the user to have its ban revoked
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_remove_guild_ban(struct discord *client,
                                   u64_snowflake_t guild_id,
                                   u64_snowflake_t user_id,
                                   struct discord_ret *ret);

/**
 * @brief Get guild roles
 *
 * @param client the client created with discord_init()
 * @param guild_id guild to get roles from
 * @CCORD_ret_list{ret, role}
 * @CCORD_return
 */
CCORDcode discord_get_guild_roles(struct discord *client,
                                  u64_snowflake_t guild_id,
                                  struct discord_ret_roles *ret);

/**
 * @brief Create a new guild role
 * @note Requires MANAGE_ROLES permission
 * @note Fires a `Guild Role Create` event
 *
 * @param client the client created with discord_init()
 * @param guild_id guild to add a role to
 * @param params request parameters
 * @CCORD_ret_obj{ret, role}
 * @CCORD_return
 */
CCORDcode discord_create_guild_role(struct discord *client,
                                    u64_snowflake_t guild_id,
                                    struct discord_create_guild_role *params,
                                    struct discord_ret_role *ret);

/**
 * @brief Begin guild prune operation
 * @note Discord recommends for larger servers to set "compute_prune_count" to
 *       false
 * @note Requires the KICK_MEMBERS permission
 * @note Fires multiple `Guild Member Remove` events
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to start the prune
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_begin_guild_prune(struct discord *client,
                                    u64_snowflake_t guild_id,
                                    struct discord_begin_guild_prune *params,
                                    struct discord_ret *ret);

/**
 * @brief Get guild invites
 *
 * @note requires the MANAGE_GUILD permission
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to get invites from
 * @CCORD_ret_list{ret, invite}
 * @CCORD_return
 */
CCORDcode discord_get_guild_invites(struct discord *client,
                                    u64_snowflake_t guild_id,
                                    struct discord_ret_invites *ret);

/**
 * @brief Deletes the integration for the guild. It will also delete any
 * associated webhooks and bots
 * @note Requires the MANAGE_GUILD permission
 * @note Fires a `Guild Integrations Update` event
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to delete the integrations from
 * @param integration_id the id of the integration to delete
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_guild_integrations(struct discord *client,
                                            u64_snowflake_t guild_id,
                                            u64_snowflake_t integration_id,
                                            struct discord_ret *ret);

/**
 * @brief Get invite from a given guild
 * @note Requires the MANAGE_GUILD permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to get vanity url from
 * @CCORD_ret_obj{ret, invite}
 * @CCORD_return
 */
CCORDcode discord_get_guild_vanity_url(struct discord *client,
                                       u64_snowflake_t guild_id,
                                       struct discord_ret_invite *ret);

/**
 * @brief Get the Welcome Screen for the guild
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to get welcome screen of
 * @CCORD_ret_obj{ret, welcome_screen}
 * @CCORD_return
 */
CCORDcode discord_get_guild_welcome_screen(
    struct discord *client,
    u64_snowflake_t guild_id,
    struct discord_ret_welcome_screen *ret);

/**
 * @brief Modify the positions of a given role list for the guild
 * @note Requires the MANAGE_ROLES permission
 * @note Fires multiple `Guild Role Update` events
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to get welcome screen of
 * @param params request parameters
 * @CCORD_ret_list{ret, role}
 * @CCORD_return
 */
CCORDcode discord_modify_guild_role_positions(
    struct discord *client,
    u64_snowflake_t guild_id,
    struct discord_modify_guild_role_positions **params,
    struct discord_ret_roles *ret);

/**
 * @brief Modify a guild role
 * @note Requires the MANAGE_ROLES permission
 * @note Fires a `Guild Role Update` event
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild that the role belongs to
 * @param role_id the unique id of the role to modify
 * @param params request parameters
 * @CCORD_ret_obj{ret, role}
 * @CCORD_return
 */
CCORDcode discord_modify_guild_role(struct discord *client,
                                    u64_snowflake_t guild_id,
                                    u64_snowflake_t role_id,
                                    struct discord_modify_guild_role *params,
                                    struct discord_ret_role *ret);

/**
 * @brief Delete a guild role
 * @note Requires the MANAGE_ROLES permission
 * @note Fires a `Guild Role Delete` event
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild that the role belongs to
 * @param role_id the unique id of the role to delete
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_guild_role(struct discord *client,
                                    u64_snowflake_t guild_id,
                                    u64_snowflake_t role_id,
                                    struct discord_ret *ret);

/**
 * @brief Get a guild template for the given code
 *
 * @param client the client created with discord_init()
 * @param code the guild template code
 * @CCORD_ret_obj{ret, guild_template}
 * @CCORD_return
 */
CCORDcode discord_get_guild_template(struct discord *client,
                                     char *code,
                                     struct discord_ret_guild_template *ret);

/**
 * @brief Creates a template for the guild
 * @note Requires the MANAGE_GUILD permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild to create a template from
 * @param params the request parameters
 * @CCORD_ret_obj{ret, guild_template}
 * @CCORD_return
 */
CCORDcode discord_create_guild_template(
    struct discord *client,
    u64_snowflake_t guild_id,
    struct discord_create_guild_template *params,
    struct discord_ret_guild_template *ret);

/**
 * @brief Syncs the template to the guild's current state
 * @note Requires the MANAGE_GUILD permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild to sync the template from
 * @param code the guild template code
 * @CCORD_ret_obj{ret, guild_template}
 * @CCORD_return
 */
CCORDcode discord_sync_guild_template(struct discord *client,
                                      u64_snowflake_t guild_id,
                                      char *code,
                                      struct discord_ret_guild_template *ret);

/**
 * @brief Get an invite for the given code
 *
 * @param client the client created with discord_init()
 * @param invite_code the invite code
 * @param params request parameters
 * @CCORD_ret_obj{ret, invite}
 * @CCORD_return
 */
CCORDcode discord_get_invite(struct discord *client,
                             char *invite_code,
                             struct discord_get_invite *params,
                             struct discord_ret_invite *ret);

/**
 * @brief Delete an invite
 * @note Requires the MANAGE_CHANNELS permission on the channel this invite
 *        belongs to, or MANAGE_GUILD to remove any invite across the guild.
 * @note Fires a `Invite Delete` event
 *
 * @param client the client created with discord_init()
 * @param invite_code the invite code
 * @CCORD_ret_obj{ret, invite}
 * @CCORD_return
 */
CCORDcode discord_delete_invite(struct discord *client,
                                char *invite_code,
                                struct discord_ret_invite *ret);

/**
 * @brief Get client's user
 *
 * @param client the client created with discord_init()
 * @CCORD_ret_obj{ret, user}
 * @CCORD_return
 */
CCORDcode discord_get_current_user(struct discord *client,
                                   struct discord_ret_user *ret);

/**
 * @brief Get user for a given id
 *
 * @param client the client created with discord_init()
 * @param user_id user to be fetched
 * @CCORD_ret_obj{ret, user}
 * @CCORD_return
 */
CCORDcode discord_get_user(struct discord *client,
                           u64_snowflake_t user_id,
                           struct discord_ret_user *ret);

/**
 * @brief Modify client's user account settings
 *
 * @param client the client created with discord_init()
 * @param params request parameters
 * @CCORD_ret_obj{ret, user}
 * @CCORD_return
 */
CCORDcode discord_modify_current_user(
    struct discord *client,
    struct discord_modify_current_user *params,
    struct discord_ret_user *ret);

/**
 * @brief Get guilds client is a member of
 * @note Requires the `guilds` oauth2 scope
 *
 * @param client the client created with discord_init()
 * @CCORD_ret_list{ret, guild}
 * @CCORD_return
 */
CCORDcode discord_get_current_user_guilds(struct discord *client,
                                          struct discord_ret_guilds *ret);

/**
 * @brief Leave a guild
 *
 * @param client the client created with discord_init()
 * @param guild_id guild to exit from
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_leave_guild(struct discord *client,
                              u64_snowflake_t guild_id,
                              struct discord_ret *ret);

/**
 * @brief Create a new DM channel with a given user
 * @warning DMs should generally be initiated by a user action. If you open a
 *        significant amount of DMs too quickly, your bot may be rate limited
 *        or blocked from opening new ones
 *
 * @param client the client created with discord_init()
 * @param params the request parameters
 * @CCORD_ret_obj{ret, channel}
 * @CCORD_return
 */
CCORDcode discord_create_dm(struct discord *client,
                            struct discord_create_dm *params,
                            struct discord_ret_channel *ret);

/**
 * @brief Create a new group DM channel with multiple users
 * @note DMs created with this function will not be shown in the Discord client
 * @note Limited to 10 active group DMs
 *
 * @param client the client created with discord_init()
 * @param params the request parameters
 * @CCORD_ret_obj{ret, channel}
 * @CCORD_return
 */
CCORDcode discord_create_group_dm(struct discord *client,
                                  struct discord_create_group_dm *params,
                                  struct discord_ret_channel *ret);

/**
 * @brief Get a list of connection objects
 * @note Requires the `connections` oauth2 scope
 *
 * @param client the client created with discord_init()
 * @CCORD_ret_list{ret, connection}
 * @CCORD_return
 */
CCORDcode discord_get_user_connections(struct discord *client,
                                       struct discord_ret_connections *ret);

/**
 * @brief Get voice regions that can be used when setting a
 *        voice or stage channel's `rtc_region`
 *
 * @param client the client created with discord_init()
 * @CCORD_ret_list{ret, voice_region}
 * @CCORD_return
 */
CCORDcode discord_list_voice_regions(struct discord *client,
                                     struct discord_ret_voice_regions *ret);

/**
 * @brief Create a new webhook
 * @note Requires the MANAGE_WEBHOOKS permission
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel that the webhook belongs to
 * @param params request parameters
 * @CCORD_ret_obj{ret, webhook}
 * @CCORD_return
 */
CCORDcode discord_create_webhook(struct discord *client,
                                 u64_snowflake_t channel_id,
                                 struct discord_create_webhook *params,
                                 struct discord_ret_webhook *ret);

/**
 * @brief Get webhooks from a given channel
 * @note Requires the MANAGE_WEBHOOKS permission
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel that the webhooks belongs to
 * @CCORD_ret_list{ret, webhook}
 * @CCORD_return
 */
CCORDcode discord_get_channel_webhooks(struct discord *client,
                                       u64_snowflake_t channel_id,
                                       struct discord_ret_webhooks *ret);

/**
 * @brief Get webhooks from a given guild webhook objects
 * @note Requires the MANAGE_WEBHOOKS permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild that the webhooks belongs to
 * @CCORD_ret_list{ret, webhook}
 * @CCORD_return
 */
CCORDcode discord_get_guild_webhooks(struct discord *client,
                                     u64_snowflake_t guild_id,
                                     struct discord_ret_webhooks *ret);

/**
 * @brief Get the new webhook object for the given id
 *
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @CCORD_ret_obj{ret, webhook}
 * @CCORD_return
 */
CCORDcode discord_get_webhook(struct discord *client,
                              u64_snowflake_t webhook_id,
                              struct discord_ret_webhook *ret);

/**
 * Same as discord_get_webhook(), except this call does not require
 *        authentication and returns no user in the webhook object
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @CCORD_ret_obj{ret, webhook}
 * @CCORD_return
 */
CCORDcode discord_get_webhook_with_token(struct discord *client,
                                         u64_snowflake_t webhook_id,
                                         const char webhook_token[],
                                         struct discord_ret_webhook *ret);

/**
 * @brief Modify a webhook
 * @note Requires the MANAGE_WEBHOOKS permission
 *
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param params request parameters
 * @CCORD_ret_obj{ret, webhook}
 * @CCORD_return
 */
CCORDcode discord_modify_webhook(struct discord *client,
                                 u64_snowflake_t webhook_id,
                                 struct discord_modify_webhook *params,
                                 struct discord_ret_webhook *ret);

/**
 * Same discord_modify_webhook(), except this call does not require
 *       authentication and returns no user in the webhook object
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @param params request parameters
 * @CCORD_ret_obj{ret, webhook}
 * @CCORD_return
 */
CCORDcode discord_modify_webhook_with_token(
    struct discord *client,
    u64_snowflake_t webhook_id,
    const char webhook_token[],
    struct discord_modify_webhook_with_token *params,
    struct discord_ret_webhook *ret);

/**
 * Delete a webhook permanently. Requires the MANAGE_WEBHOOKS permission
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_webhook(struct discord *client,
                                 u64_snowflake_t webhook_id,
                                 struct discord_ret *ret);

/**
 * Same discord_delete_webhook(), except this call does not require
 *       authentication
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_webhook_with_token(struct discord *client,
                                            u64_snowflake_t webhook_id,
                                            const char webhook_token[],
                                            struct discord_ret *ret);

/**
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @param params request parameters
 * @CCORD_ret_obj{ret, webhook}
 * @CCORD_return
 */
CCORDcode discord_execute_webhook(struct discord *client,
                                  u64_snowflake_t webhook_id,
                                  const char webhook_token[],
                                  struct discord_execute_webhook *params,
                                  struct discord_ret_webhook *ret);

/**
 * @brief Get previously-sent webhook message from the same token
 *
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @param message_id the message the webhook belongs to
 * @CCORD_ret_obj{ret, message}
 * @CCORD_return
 */
CCORDcode discord_get_webhook_message(struct discord *client,
                                      u64_snowflake_t webhook_id,
                                      const char webhook_token[],
                                      u64_snowflake_t message_id,
                                      struct discord_ret_message *ret);

/**
 * @brief Edits a previously-sent webhook message from the same token
 *
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @param message_id the message the webhook belongs to
 * @param params request parameters
 * @CCORD_ret_obj{ret, message}
 * @CCORD_return
 */
CCORDcode discord_edit_webhook_message(
    struct discord *client,
    u64_snowflake_t webhook_id,
    const char webhook_token[],
    u64_snowflake_t message_id,
    struct discord_edit_webhook_message *params,
    struct discord_ret_message *ret);

/**
 * @brief Deletes a message that was created by the webhook
 *
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @param message_id the message the webhook belongs to
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_webhook_message(struct discord *client,
                                         u64_snowflake_t webhook_id,
                                         const char webhook_token[],
                                         u64_snowflake_t message_id,
                                         struct discord_ret *ret);

/**
 * @brief Get a single valid WSS URL, which the client can use for connecting
 * @note This route should be cached, and only call the function again if
 *        unable to properly establishing a connection with the cached version
 *
 * @param client the client created with discord_init()
 * @param ret if successful, a @ref sized_buffer containing the JSON response
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_get_gateway(struct discord *client, struct discord_ret *ret);

/**
 * @brief Get a single valid WSS URL, and additional metadata that can help
 *        during the operation of large bots.
 * @note This route should not be cached for extended periods of time as the
 *        value is not guaranteed to be the same per-call, and changes as the
 *        bot joins/leaves guilds
 *
 * @param client the client created with discord_init()
 * @param ret if successful, a @ref sized_buffer containing the JSON response
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_get_gateway_bot(struct discord *client,
                                  struct discord_ret *ret);

/**
 * @brief Disconnect a member from voice channel
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild the member belongs to
 * @param user_id the user to be disconnected
 * @CCORD_ret_obj{ret, guild_member}
 * @CCORD_return
 */
CCORDcode discord_disconnect_guild_member(
    struct discord *client,
    u64_snowflake_t guild_id,
    u64_snowflake_t user_id,
    struct discord_ret_guild_member *ret);

/**
 * @brief Get a guild's channel from its given numerical position
 *
 * @param client the client created with discord_init()
 * @param guild_id guild the channel belongs to
 * @param type the channel type where to take position reference from
 * @CCORD_ret_obj{ret, channel}
 * @CCORD_return
 */
CCORDcode discord_get_channel_at_pos(struct discord *client,
                                     u64_snowflake_t guild_id,
                                     enum discord_channel_types type,
                                     size_t position,
                                     struct discord_ret_channel *ret);

/******************************************************************************
 * Functions specific to Discord's Gateway
 ******************************************************************************/

/**
 * @brief return value of discord_set_event_scheduler() callback
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
typedef enum discord_event_scheduler (*discord_ev_scheduler)(
    struct discord *client,
    struct sized_buffer *event_data,
    enum discord_gateway_events event);

/**
 * @brief Provides the user with a fine-grained control of the Discord's
 *       event-loop
 *
 * Allows the user to specify which events should be executed from the
 *       main-thread, in parallel from a worker-thread, or completely ignored
 *
 * @param client the client created_with discord_init()
 * @param fn the function that will be executed
 * @warning The user is responsible for providing his own locking mechanism to
 *       avoid race-condition on sensitive data
 * @see @ref discord_event_scheduler, @ref discord_gateway_events
 */
void discord_set_event_scheduler(struct discord *client,
                                 discord_ev_scheduler callback);

/** @defgroup DiscordCallbackTypes
 *  @{ */

typedef void (*discord_ev_idle)(struct discord *client);
typedef void (*discord_ev_application_command)(
    struct discord *client, const struct discord_application_command *app_cmd);
typedef void (*discord_ev_channel)(struct discord *client,
                                   const struct discord_channel *channel);
typedef void (*discord_ev_channel_pins_update)(
    struct discord *client,
    u64_snowflake_t guild_id,
    u64_snowflake_t channel_id,
    u64_unix_ms_t last_pin_timestamp);
typedef void (*discord_ev_guild)(struct discord *client,
                                 const struct discord_guild *guild);
typedef void (*discord_ev_guild_delete)(struct discord *client,
                                        u64_snowflake_t guild_id);
typedef void (*discord_ev_guild_role)(struct discord *client,
                                      u64_snowflake_t guild_id,
                                      const struct discord_role *role);
typedef void (*discord_ev_guild_role_delete)(struct discord *client,
                                             u64_snowflake_t guild_id,
                                             u64_snowflake_t role_id);
typedef void (*discord_ev_guild_member)(
    struct discord *client,
    u64_snowflake_t guild_id,
    const struct discord_guild_member *member);
typedef void (*discord_ev_guild_member_remove)(
    struct discord *client,
    u64_snowflake_t guild_id,
    const struct discord_user *user);
typedef void (*discord_ev_guild_ban)(struct discord *client,
                                     u64_snowflake_t guild_id,
                                     const struct discord_user *user);
typedef void (*discord_ev_interaction)(
    struct discord *client, const struct discord_interaction *interaction);
typedef void (*discord_ev_message)(struct discord *client,
                                   const struct discord_message *message);
typedef void (*discord_ev_message_delete)(struct discord *client,
                                          u64_snowflake_t id,
                                          u64_snowflake_t channel_id,
                                          u64_snowflake_t guild_id);
typedef void (*discord_ev_message_delete_bulk)(struct discord *client,
                                               const u64_snowflake_t **ids,
                                               u64_snowflake_t channel_id,
                                               u64_snowflake_t guild_id);
typedef void (*discord_ev_message_reaction_add)(
    struct discord *client,
    u64_snowflake_t user_id,
    u64_snowflake_t channel_id,
    u64_snowflake_t message_id,
    u64_snowflake_t guild_id,
    const struct discord_guild_member *member,
    const struct discord_emoji *emoji);
typedef void (*discord_ev_message_reaction_remove)(
    struct discord *client,
    u64_snowflake_t user_id,
    u64_snowflake_t channel_id,
    u64_snowflake_t message_id,
    u64_snowflake_t guild_id,
    const struct discord_emoji *emoji);
typedef void (*discord_ev_message_reaction_remove_all)(
    struct discord *client,
    u64_snowflake_t channel_id,
    u64_snowflake_t message_id,
    u64_snowflake_t guild_id);
typedef void (*discord_ev_message_reaction_remove_emoji)(
    struct discord *client,
    u64_snowflake_t channel_id,
    u64_snowflake_t message_id,
    u64_snowflake_t guild_id,
    const struct discord_emoji *emoji);
typedef void (*discord_ev_voice_state_update)(
    struct discord *client, const struct discord_voice_state *voice_state);
typedef void (*discord_ev_voice_server_update)(struct discord *client,
                                               const char *token,
                                               u64_snowflake_t guild_id,
                                               const char *endpoint);
/** @} */

/**
 * @brief Set command/callback pair
 *
 * The callback is triggered when a user types the assigned command in a
 *        chat visible to the client
 * @param client the client created with discord_init()
 * @param command the command to trigger the callback
 * @param callback the callback to be triggered on event
 * @note The command and any subjacent empty space is left out of
 *       the message content
 */
void discord_set_on_command(struct discord *client,
                            char *command,
                            discord_ev_message callback);

/**
 * @brief Set a variadic series of NULL terminated commands to a callback
 *
 * The callback is triggered when a user types one of the assigned commands in
 *        a chat visble to the client
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 * @param ... commands and a NULL terminator
 * @note The command and any subjacent empty space is left out of
 *       the message content
 */
void discord_set_on_commands(struct discord *client,
                             discord_ev_message callback,
                             ...);

/** @defgroup DiscordCallbackSet
 * @brief Set callbacks to be triggered on event detection
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 * @note the functions will automatically set the necessary intent(s) to make
 *        the callback triggerable
 *  @{ */

/** @brief Triggers at every event-loop iteration.  */
void discord_set_on_idle(struct discord *client, discord_ev_idle callback);
/** @brief Triggers when the client is ready */
void discord_set_on_ready(struct discord *client, discord_ev_idle callback);
/** @brief Triggers when a application command is created */
void discord_set_on_application_command_create(
    struct discord *client, discord_ev_application_command callback);
/** @brief Triggers when a application command is updated */
void discord_set_on_application_command_update(
    struct discord *client, discord_ev_application_command callback);
/** @brief Triggers when a application command is deleted */
void discord_set_on_application_command_delete(
    struct discord *client, discord_ev_application_command callback);
/** @brief Triggers when a channel is created */
void discord_set_on_channel_create(struct discord *client,
                                   discord_ev_channel callback);
/** @brief Triggers when a channel is updated */
void discord_set_on_channel_update(struct discord *client,
                                   discord_ev_channel callback);
/** @brief Triggers when a channel is deleted */
void discord_set_on_channel_delete(struct discord *client,
                                   discord_ev_channel callback);
/** @brief Triggers when some channel pins are updated */
void discord_set_on_channel_pins_update(
    struct discord *client, discord_ev_channel_pins_update callback);
/** @brief Triggers when a thread is created */
void discord_set_on_thread_create(struct discord *client,
                                  discord_ev_channel callback);
/** @brief Triggers when a thread is updated */
void discord_set_on_thread_update(struct discord *client,
                                  discord_ev_channel callback);
/** @brief Triggers when a thread is deleted */
void discord_set_on_thread_delete(struct discord *client,
                                  discord_ev_channel callback);
/** @brief Triggers when guild information becomes available */
void discord_set_on_guild_create(struct discord *client,
                                 discord_ev_guild callback);
/** @brief Triggers when a guild's information becomes updated */
void discord_set_on_guild_update(struct discord *client,
                                 discord_ev_guild callback);
/** @brief Triggers when removed from a guild */
void discord_set_on_guild_delete(struct discord *client,
                                 discord_ev_guild_delete callback);
/** @brief Triggers when a guild role is created */
void discord_set_on_guild_role_create(struct discord *client,
                                      discord_ev_guild_role callback);
/** @brief Triggers when a guild role is updated */
void discord_set_on_guild_role_update(struct discord *client,
                                      discord_ev_guild_role callback);
/** @brief Triggers when a guild role is deleted */
void discord_set_on_guild_role_delete(struct discord *client,
                                      discord_ev_guild_role_delete callback);
/** @brief Triggers when a guild member is added */
void discord_set_on_guild_member_add(struct discord *client,
                                     discord_ev_guild_member callback);
/** @brief Triggers when a guild member is updated */
void discord_set_on_guild_member_update(struct discord *client,
                                        discord_ev_guild_member callback);
/** @brief Triggers when a guild member is removed */
void discord_set_on_guild_member_remove(
    struct discord *client, discord_ev_guild_member_remove callback);
/** @brief Triggers when a guild ban is added */
void discord_set_on_guild_ban_add(struct discord *client,
                                  discord_ev_guild_ban callback);
/** @brief Triggers when a guild ban is removed */
void discord_set_on_guild_ban_remove(struct discord *client,
                                     discord_ev_guild_ban callback);
/** @brief Triggers when a interaction is created */
void discord_set_on_interaction_create(struct discord *client,
                                       discord_ev_interaction callback);
/** @brief Triggers when a message is created */
void discord_set_on_message_create(struct discord *client,
                                   discord_ev_message callback);
/** @brief Triggers when a message is updated */
void discord_set_on_message_update(struct discord *client,
                                   discord_ev_message callback);
/** @brief Triggers when a message is deleted */
void discord_set_on_message_delete(struct discord *client,
                                   discord_ev_message_delete callback);
/** @brief Triggers when a bulk of messages are deleted */
void discord_set_on_message_delete_bulk(
    struct discord *client, discord_ev_message_delete_bulk callback);
/** @brief Triggers when a message reaction is added */
void discord_set_on_message_reaction_add(
    struct discord *client, discord_ev_message_reaction_add callback);
/** @brief Triggers when a message reaction is removed */
void discord_set_on_message_reaction_remove(
    struct discord *client, discord_ev_message_reaction_remove callback);
/** @brief Triggers when all reaction from some message is removed
 */
void discord_set_on_message_reaction_remove_all(
    struct discord *client, discord_ev_message_reaction_remove_all callback);
/** @brief Triggers when all instances of a particular reaction from some
 *        message is removed */
void discord_set_on_message_reaction_remove_emoji(
    struct discord *client, discord_ev_message_reaction_remove_emoji callback);
/** @brief Triggers when a voice state is updated */
void discord_set_on_voice_state_update(struct discord *client,
                                       discord_ev_voice_state_update callback);
/** @brief Triggers when a voice server is updated */
void discord_set_on_voice_server_update(
    struct discord *client, discord_ev_voice_server_update callback);

/** @} */

/******************************************************************************
 * Dynamic builder functions
 ******************************************************************************/

/**
 * @brief Add title to embed
 * @note the embed must be freed with `discord_embed_cleanup()` after its no
 * longer being used
 *
 * @param embed the embed being modified
 * @param format printf-like formatting string
 * @param ... variadic arguments to be matched to format
 */
void discord_embed_set_title(struct discord_embed *embed, char format[], ...);

/**
 * @brief Add description to embed
 * @note the embed must be freed with `discord_embed_cleanup()` after its no
 * longer being used
 *
 * @param embed the embed being modified
 * @param format printf-like formatting string
 * @param ... variadic arguments to be matched to format
 */
void discord_embed_set_description(struct discord_embed *embed,
                                   char format[],
                                   ...);

/**
 * @brief Add URL to embed
 * @note the embed must be freed with `discord_embed_cleanup()` after its no
 * longer being used
 *
 * @param embed the embed being modified
 * @param format printf-like formatting string
 * @param ... variadic arguments to be matched to format
 */
void discord_embed_set_url(struct discord_embed *embed, char format[], ...);

/**
 * @brief Add thumbnail to embed
 * @note the embed must be freed with `discord_embed_cleanup()` after its no
 * longer being used
 *
 * @param embed the embed being modified
 * @param url source url of thumbnail
 * @param proxy_url a proxied url of the thumbnail
 * @param height height of thumbnail
 * @param width width of thumbnail
 */
void discord_embed_set_thumbnail(struct discord_embed *embed,
                                 char url[],
                                 char proxy_url[],
                                 int height,
                                 int width);

/**
 * @brief Add image to embed
 * @note the embed must be freed with `discord_embed_cleanup()` after its no
 * longer being used
 *
 * @param embed the embed being modified
 * @param url source url of image
 * @param proxy_url a proxied url of the image
 * @param height height of image
 * @param width width of image
 */
void discord_embed_set_image(struct discord_embed *embed,
                             char url[],
                             char proxy_url[],
                             int height,
                             int width);

/**
 * @brief Add video to embed
 * @note the embed must be freed with `discord_embed_cleanup()` after its no
 * longer being used
 *
 * @param embed the embed being modified
 * @param url source url of video
 * @param proxy_url a proxied url of the video
 * @param height height of video
 * @param width width of video
 */
void discord_embed_set_video(struct discord_embed *embed,
                             char url[],
                             char proxy_url[],
                             int height,
                             int width);

/**
 * @brief Add footer to embed
 * @note the embed must be freed with `discord_embed_cleanup()` after its no
 * longer being used
 *
 * @param embed the embed being modified
 * @param text footer text
 * @param icon_url url of footer icon
 * @param proxy_icon_url a proxied url of footer icon
 */
void discord_embed_set_footer(struct discord_embed *embed,
                              char text[],
                              char icon_url[],
                              char proxy_icon_url[]);

/**
 * @brief Add provider to embed
 * @note the embed must be freed with `discord_embed_cleanup()` after its no
 * longer being used
 *
 * @param embed the embed being modified
 * @param name name of provider
 * @param url url of provider
 */
void discord_embed_set_provider(struct discord_embed *embed,
                                char name[],
                                char url[]);

/**
 * @brief Add author to embed
 * @note the embed must be freed with `discord_embed_cleanup()` after its no
 *        longer being used
 *
 * @param embed the embed being modified
 * @param name name of author
 * @param url url of author
 * @param icon_url url of author icon
 * @param proxy_icon_url a proxied url of author icon
 */
void discord_embed_set_author(struct discord_embed *embed,
                              char name[],
                              char url[],
                              char icon_url[],
                              char proxy_icon_url[]);

/**
 * @brief Add field to embed
 * @note the embed must be freed with `discord_embed_cleanup()` after its no
 *        longer being used
 *
 * @param embed the embed being modified
 * @param name name of the field
 * @param value value of the field
 * @param Inline whether or not this field should display inline
 */
void discord_embed_add_field(struct discord_embed *embed,
                             char name[],
                             char value[],
                             bool Inline);

/**
 * @brief Append to an overwrite list
 * @note the list should be freed with `discord_overwrite_list_free()` after
 *        its no longer being used
 *
 * @param permission_overwrites list to be appended to
 * @param id role or user id
 * @param type either 0 (role) or 1 (member)
 * @param allow permission bit set
 * @param deny permission bit set
 */
void discord_overwrite_append(
    struct discord_overwrite ***permission_overwrites,
    u64_snowflake_t id,
    int type,
    u64_bitmask_t allow,
    u64_bitmask_t deny);

/**
 * @brief Helper function to add presence activities
 * @see discord_set_presence()
 *
 * This function is a wrapper over ntl_append2()
 */
void discord_presence_add_activity(struct discord_presence_status *presence,
                                   struct discord_activity *activity);

#endif /* DISCORD_H */
