/**
 * @file discord.h
 * @author Cogmasters
 * @brief Public functions and datatypes
 *
 * These symbols are organized in a intuitive fashion to be easily
 *        matched to the official Discord API docs
 * @see https://discord.com/developers/docs/intro
 */

#ifndef DISCORD_H
#define DISCORD_H

#include <stdbool.h>

#include "common.h"
#include "logconf.h"

#define DISCORD_API_BASE_URL       "https://discord.com/api/v9"
#define DISCORD_GATEWAY_URL_SUFFIX "?v=9&encoding=json"

/* forward declaration */
struct discord;
/**/

#include "discord-codecs.h"
#ifdef HAS_DISCORD_VOICE
#include "discord-voice.h"
#endif /* HAS_DISCORD_VOICE */
#include "discord-templates.h"

/** @brief Request's return context */
struct discord_ret {
    /** optional callback to be executed on a successful request */
    void (*done)(struct discord *client, void *data);
    DISCORDT_RET_DEFAULT_FIELDS;
    /** if `true`, request will block the thread and perform on-spot */
    bool sync;
};

/** @brief flag for enabling `sync` mode without expecting a datatype return */
#define DISCORD_SYNC_FLAG ((void *)-1)

#include "audit_log.h"
#include "invite.h"
#include "channel.h"
#include "emoji.h"
#include "guild.h"
#include "guild_template.h"
#include "user.h"
#include "voice.h"
#include "webhook.h"
#include "application_command.h"
#include "interaction.h"
#include "gateway.h"

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
 * @deprecated this function will be removed in the future
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
void discord_add_intents(struct discord *client, uint64_t code);
/**
 * @brief Unsubscribe from Discord Events
 *
 * @param client the client created with discord_init()
 * @param code the intents opcode, can be set as bitmask operation
 *        Ex: 1 << 0 | 1 << 1 | 1 << 4
 *
 */
void discord_remove_intents(struct discord *client, uint64_t code);
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
 * @warning the user should provide their own locking mechanism to protect
 *        its data from race conditions
 */
void *discord_set_data(struct discord *client, void *data);

/**
 * @brief Receive user arbitrary data stored with discord_set_data()
 *
 * @param client the client created with discord_init()
 * @return pointer to user data
 * @warning the user should provide their own locking mechanism to protect
 *        its data from race conditions
 */
void *discord_get_data(struct discord *client);

/**
 * @brief Set the Client presence state
 * @see discord_presence_add_activity()
 *
 * @param client the client created with discord_init()
 * @param presence change the client's status to it
 */
void discord_set_presence(struct discord *client,
                          struct discord_presence_update *presence);

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

#endif /* DISCORD_H */
