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

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <inttypes.h>
#include <stdbool.h>

#include "logconf.h"
#include "error.h"
#include "types.h"
#include "concord-once.h"
#include "io_poller.h"

#define DISCORD_API_BASE_URL       "https://discord.com/api/v9"
#define DISCORD_GATEWAY_URL_SUFFIX "?v=9&encoding=json"

/* forward declaration */
struct discord;
/**/

#include "discord_codecs.h"
#ifdef CCORD_VOICE
#include "discord-voice.h"
#endif /* CCORD_VOICE */
#include "discord-response.h"

/** @defgroup DiscordConstants Constants
 * @brief Macros for constants defined by Discord
 * @note macros assume the worst-case scenario for strings, where each
 *      character is 4 bytes long (UTF8)
 *  @{ */

/** @defgroup DiscordConstantsGeneral General lengths
 * @brief Max length for general fields
 *  @{ */
#define DISCORD_MAX_NAME_LEN          4 * 100 + 1
#define DISCORD_MAX_TOPIC_LEN         4 * 1024 + 1
#define DISCORD_MAX_DESCRIPTION_LEN   4 * 2048 + 1
#define DISCORD_MAX_USERNAME_LEN      4 * 32 + 1
#define DISCORD_MAX_DISCRIMINATOR_LEN 4 + 1
#define DISCORD_MAX_REASON_LEN        4 * 512 + 1
#define DISCORD_MAX_MESSAGE_LEN       4 * 2000 + 1
#define DISCORD_MAX_PAYLOAD_LEN       4 * 4096 + 1
/** @} DiscordConstantsGeneral */

/** @defgroup DiscordConstantsEmbed Embed lengths
 * @brief Max length for embed fields
 *  @{ */
#define DISCORD_EMBED_TITLE_LEN       4 * 256 + 1
#define DISCORD_EMBED_DESCRIPTION_LEN 4 * 2048 + 1
#define DISCORD_EMBED_MAX_FIELDS      25
#define DISCORD_EMBED_FIELD_NAME_LEN  4 * 256 + 1
#define DISCORD_EMBED_FIELD_VALUE_LEN 4 * 1024 + 1
#define DISCORD_EMBED_FOOTER_TEXT_LEN 4 * 2048 + 1
#define DISCORD_EMBED_AUTHOR_NAME_LEN 4 * 256 + 1
/** @} DiscordConstantsEmbed */

/** @defgroup DiscordConstantsWebhook Webhook lengths
 * @brief Max length for embed fields
 *  @{ */
#define DISCORD_WEBHOOK_NAME_LEN 4 * 80 + 1
/** @} DiscordConstantsWebhook */

/** @} DiscordConstants */

/** @addtogroup ConcordError
 *  @{ */

/** Received a JSON error message */
#define CCORD_DISCORD_JSON_CODE 1
/** Bad authentication token */
#define CCORD_DISCORD_BAD_AUTH 2
/** Being ratelimited */
#define CCORD_DISCORD_RATELIMIT 3
/** Couldn't establish connection to Discord */
#define CCORD_DISCORD_CONNECTION 4

/**
 * @brief Return a Concord's error
 * @note used to log and return an error
 *
 * @param client the client created with discord_init(), NULL for generic error
 * @param error the error string to be logged
 * @param code the error code
 * @return the error code
 */
CCORDcode discord_return_error(struct discord *client,
                               const char error[],
                               CCORDcode code);

/**
 * @brief Return the meaning of CCORDcode
 *
 * @param code the CCORDcode value
 * @param client @note unused parameter
 * @return a string containing the code meaning
 */
const char *discord_strerror(CCORDcode code, struct discord *client);

/** @} ConcordError */

/** @defgroup DiscordAPI API
 *   @brief The Discord public API supported by Concord
 *  @{ */

#include "audit_log.h"
#include "invite.h"
#include "channel.h"
#include "emoji.h"
#include "guild.h"
#include "guild_template.h"
#include "user.h"
#include "voice.h"
#include "webhook.h"
#include "gateway.h"
/** @defgroup DiscordAPIInteractions Interactions
 *   @brief Interactions public API supported by Concord
 *  @{ */
#include "application_command.h"
#include "interaction.h"
/** @} DiscordAPIInteractions */

/** @} DiscordAPI */

/** @defgroup Discord Client
 *   @brief Functions and datatypes for the client
 *  @{ */

/** @struct discord */

#include "discord-events.h"

/**
 * @brief Claim ownership of a function parameter provided by Concord
 * @see discord_unclaim()
 *
 * @param client the client initialized with discord_init()
 * @param param a function parameter provided by Concord
 * @return pointer to `param` (for one-liners)
 */
#define discord_claim(client, param) (__discord_claim(client, param), param)
void __discord_claim(struct discord *client, const void *data);

/**
 * @brief Unclaim ownership of a function parameter provided by Concord
 * @note this will trigger the cleanup method of the parameter, so this should
 *      only be called when you no longer plan to use it
 * @see discord_claim()
 *
 * @param client the client initialized with discord_init()
 * @param param a function parameter provided by Concord, that has been
 *      previously claimed with discord_claim()
 */
void discord_unclaim(struct discord *client, const void *data);

/**
 * @brief Create a Discord Client handle by its token
 * @see discord_get_logconf() to configure logging behavior
 *
 * @param token the bot token
 * @return the newly created Discord Client handle
 */
struct discord *discord_init(const char token[]);

/**
 * @brief Create a Discord Client handle by a `config.json` file
 *
 * @param config_file the `config.json` file name
 * @return the newly created Discord Client handle
 */
struct discord *discord_config_init(const char config_file[]);

/**
 * @brief Get the contents from the config file field
 * @note only works if your bot has been initialized with discord_config_init()
 *
 * @param client the client created with discord_config_init()
 * @param path the JSON key path
 * @param depth the path depth
 * @return a read-only sized buffer containing the field's contents
 */
struct ccord_szbuf_readonly discord_config_get_field(struct discord *client,
                                                     char *const path[],
                                                     unsigned depth);

/**
 * @brief Clone a discord client
 *
 * Should be called before entering a thread, to ensure each thread
 *        has its own client instance with unique buffers, url and headers
 * @param orig the original client created with discord_init()
 * @return the client clone
 */

struct discord *discord_clone(const struct discord *orig);

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
 * @brief Set the client presence status
 * @deprecated since v2.0.0, use discord_update_presence() instead
 * @see discord_presence_add_activity()
 *
 * @param client the client created with discord_init()
 * @param presence status to update the client's to
 */
void discord_set_presence(struct discord *client,
                          struct discord_presence_update *presence);

/**
 * @brief Request all members for a guild or a list of guilds
 *
 * @param client the client created with discord_init()
 * @param request request guild members information
 */
void discord_request_guild_members(
    struct discord *client, struct discord_request_guild_members *request);

/**
 * @brief Sent when a client wants to join, move or disconnect from a voice
 *      channel
 *
 * @param client the client created with discord_init()
 * @param update request guild members information
 */
void discord_update_voice_state(struct discord *client,
                                struct discord_update_voice_state *update);

/**
 * @brief Update the client presence status
 * @see discord_presence_add_activity()
 *
 * @param client the client created with discord_init()
 * @param presence status to update the client's to
 */
void discord_update_presence(struct discord *client,
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
 * @brief Get the current timestamp (in microseconds)
 *
 * @param client the client created with discord_init()
 * @return the timestamp in microseconds
 */
uint64_t discord_timestamp_us(struct discord *client);

/**
 * @brief Retrieve client's logging module for configuration purposes
 * @see logconf_setup(), logconf_set_quiet(), logconf_set_level()
 *
 * @param client the client created with discord_init()
 * @return the client's logging module
 */
struct logconf *discord_get_logconf(struct discord *client);

/**
 * @brief get the io_poller used by the discord client
 *
 * @param client the client created with discord_init()
 * @return struct io_poller*
 */
struct io_poller *discord_get_io_poller(struct discord *client);

/** @defgroup DiscordTimer Timer
 * @brief Schedule callbacks to be called in the future
 *  @{ */

/* forward declaration */
struct discord_timer;
/**/

/** @brief callback to be used with struct discord_timer */
typedef void (*discord_ev_timer)(struct discord *client,
                                 struct discord_timer *ev);

/** @brief flags used to change behaviour of timer */
enum discord_timer_flags {
    /** use milliseconds for interval and start_time */
    DISCORD_TIMER_MILLISECONDS = 0,
    /** use microseconds for interval and start_time */
    DISCORD_TIMER_MICROSECONDS = 1 << 0,
    /** whether or not timer is marked for deletion */
    DISCORD_TIMER_DELETE = 1 << 1,
    /** automatically delete a timer once its repeat counter runs out */
    DISCORD_TIMER_DELETE_AUTO = 1 << 2,
    /** timer has been canceled. user should cleanup only */
    DISCORD_TIMER_CANCELED = 1 << 3,

    /** used in discord_timer_ctl to get the timer's data */
    DISCORD_TIMER_GET = 1 << 5,
    /** timer should run using a fixed interval based on start time */
    DISCORD_TIMER_INTERVAL_FIXED = 1 << 6,
};

/** @brief struct used for modifying, and getting info about a timer */
struct discord_timer {
    /** the identifier used for the timer. 0 creates a new timer */
    unsigned id;
    /** the flags used to manipulate the timer */
    enum discord_timer_flags flags;
    /** the callback that should be called when timer triggers */
    discord_ev_timer cb;
    /** user data */
    void *data;
    /** delay before timer should start */
    int64_t delay;
    /** interval that the timer should repeat at. must be >= 0 */
    int64_t interval;
    /** how many times a timer should repeat (-1 == infinity) */
    int64_t repeat;
};

/**
 * @brief modifies or creates a timer
 *
 * @param client the client created with discord_init()
 * @param timer the timer that should be modified
 * @return the id of the timer
 */
unsigned discord_timer_ctl(struct discord *client,
                           struct discord_timer *timer);

/**
 * @brief creates a one shot timer that automatically
 *        deletes itself upon completion
 *
 * @param client the client created with discord_init()
 * @param cb the callback that should be called when timer triggers
 * @param data user data
 * @param delay delay before timer should start in milliseconds
 * @return the id of the timer
 */
unsigned discord_timer(struct discord *client,
                       discord_ev_timer cb,
                       void *data,
                       int64_t delay);

/**
 * @brief creates a repeating timer that automatically
 *        deletes itself upon completion
 *
 * @param client the client created with discord_init()
 * @param cb the callback that should be called when timer triggers
 * @param data user data
 * @param delay delay before timer should start in milliseconds
 * @param interval interval between runs. (-1 == disable repeat)
 * @param repeat repetitions (-1 == infinity)
 * @return the id of the timer
 */
unsigned discord_timer_interval(struct discord *client,
                                discord_ev_timer cb,
                                void *data,
                                int64_t delay,
                                int64_t interval,
                                int64_t repeat);

/**
 * @brief get the data associated with the timer
 *
 * @param client the client created with discord_init()
 * @param id id of the timer
 * @param timer where to copy the timer data to
 * @return true on success
 */
bool discord_timer_get(struct discord *client,
                       unsigned id,
                       struct discord_timer *timer);

/**
 * @brief starts a timer
 *
 * @param client the client created with discord_init()
 * @param id id of the timer
 * @return true on success
 */
bool discord_timer_start(struct discord *client, unsigned id);

/**
 * @brief stops a timer
 *
 * @param client the client created with discord_init()
 * @param id id of the timer
 * @return true on success
 */
bool discord_timer_stop(struct discord *client, unsigned id);

/**
 * @brief cancels a timer,
 * this will delete the timer if DISCORD_TIMER_DELETE_AUTO is enabled
 *
 * @param client the client created with discord_init()
 * @param id id of the timer
 * @return true on success
 */
bool discord_timer_cancel(struct discord *client, unsigned id);

/**
 * @brief deletes a timer
 *
 * @param client the client created with discord_init()
 * @param id id of the timer
 * @return true on success
 */
bool discord_timer_delete(struct discord *client, unsigned id);

/**
 * @brief cancels, and deletes a timer
 *
 * @param client the client created with discord_init()
 * @param id id of the timer
 * @return true on success
 */
bool discord_timer_cancel_and_delete(struct discord *client, unsigned id);

/** @example timers.c
 * Demonstrates the Timer API for callback scheduling */

/** @} DiscordTimer */
/** @} Discord */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DISCORD_H */
