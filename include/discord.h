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

#include "concord-error.h"
#include "types.h"
#include "io_poller.h"
#define LOGMOD_HEADER
#include "logmod.h"

#ifndef DISCORD_VERSION
/**
 * @brief The Discord API version to use
 * @warning only change this if you know what you are doing!
 */
#define DISCORD_VERSION "10"
#endif

#define DISCORD_API_BASE_URL       "https://discord.com/api/v" DISCORD_VERSION
#define DISCORD_GATEWAY_URL_SUFFIX "?v=" DISCORD_VERSION "&encoding=json"

/* forward declaration */
struct discord;
/**/

#include "discord_codecs.h"
#include "discord-response.h"

/** @defgroup DiscordClient Client */

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
#define DISCORD_EMBED_DESCRIPTION_LEN 4 * 4096 + 1
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

/* XXX: As new values are added, discord_strerror() and
 *      discord_code_as_string() should be updated accordingly! */
/** @defgroup DiscordError Discord error codes
 *  @brief Error codes triggered from Discord
 *  @{ */

/** Alias for @ref CCORD_OK */
#define CCORD_DISCORD_OK CCORD_OK
/** action is pending (ex: request has been enqueued and will be performed
 *      later) */
#define CCORD_PENDING 1
/** received a JSON error message */
#define CCORD_DISCORD_JSON_CODE 100
/** bad authentication token */
#define CCORD_DISCORD_BAD_AUTH 101
/** being ratelimited */
#define CCORD_DISCORD_RATELIMIT 102
/** couldn't establish connection to Discord */
#define CCORD_DISCORD_CONNECTION 103

/**
 * @brief Return the value of CCORDcode as a string
 *
 * @param code the CCORDcode value
 * @return the enum value as a string
 */
const char *discord_code_as_string(CCORDcode code);

/**
 * @brief Return the meaning of CCORDcode
 *
 * @param code the CCORDcode value
 * @param client @note unused parameter
 * @return a string containing the code meaning
 */
const char *discord_strerror(CCORDcode code, struct discord *client);

/** @} DiscordError */

/** @} ConcordError */

/** @defgroup DiscordAPI API
 *   @brief The Discord public API supported by Concord
 *  @{ */

#include "audit_log.h"
#include "auto_moderation.h"
#include "invite.h"
#include "channel.h"
#include "emoji.h"
#include "guild.h"
#include "guild_scheduled_event.h"
#include "guild_template.h"
#include "stage_instance.h"
#include "sticker.h"
#include "user.h"
#include "voice.h"
#include "webhook.h"
#include "gateway.h"
#include "oauth2.h"
/** @defgroup DiscordAPIInteractions Interactions
 *   @brief Interactions public API supported by Concord
 *  @{ */
#include "application_command.h"
#include "interaction.h"
/** @} DiscordAPIInteractions */

/** @} DiscordAPI */

/** @addtogroup DiscordClient
 *   @brief Client functions and datatypes
 *  @{ */

/** @struct discord */

#include "discord-cache.h"
#include "discord-events.h"

/**
 * @brief Claim ownership of a resource provided by Concord
 * @see discord_unclaim()
 *
 * @param client the client initialized with discord_from_token()
 * @param data a resource provided by Concord
 * @return pointer to `data` (for one-liners)
 */
#define discord_claim(client, data) (__discord_claim(client, data), data)
void __discord_claim(struct discord *client, const void *data);

/**
 * @brief Unclaim ownership of a resource provided by Concord
 * @note this will make the resource eligible for cleanup, so this should
 *      only be called when you no longer plan to use it
 * @see discord_claim()
 *
 * @param client the client initialized with discord_from_token()
 * @param data a resource provided by Concord, that has been
 *      previously claimed with discord_claim()
 */
void discord_unclaim(struct discord *client, const void *data);

/** @deprecated since v3.0.0, keep backwards compatibility */
#define ccord_global_init()

/** @deprecated since v3.0.0, keep backwards compatibility */
#define ccord_global_cleanup()

/**
 * @brief Gracefully notify all Discord connections for shutting down
 *
 * @note this function will not wait before returning, and will
 *      return immediately. The shutdown process will be handled
 *      in the background.
 */
void discord_shutdown_all(void);

/**
 * @brief Check if all Discord connections shutting down is in progress
 *
 * @return true if all shutdown is in progress, false otherwise
 */
bool discord_shutdown_all_ongoing(void);

/**
 * @brief Creates a Discord Client handle from a token
 * @see discord_get_logmod() to configure logging behavior
 *
 * @param token the bot token
 * @return the newly created Discord Client handle
 */
struct discord *discord_from_token(const char token[]);

/**
 * @brief Creates a Discord Client handle from a `config.json` file
 * @see discord_get_logmod() to configure logging behavior
 *
 * @param config_file the `config.json` file name
 * @return the newly created Discord Client handle
 */
struct discord *discord_from_json(const char config_file[]);

/**
 * @brief The Discord configuration handler
 *
 * This struct is used to store the Discord client configuration
 */
struct discord_config {
    /** the bot token */
    char *token;
    struct {
        /** minimum logging level */
        enum logmod_levels level;
        /** silence terminal logging */
        bool quiet;
        /** enable color to terminal logging */
        bool color;
        /** overwrite existing files */
        bool overwrite;
        /* the trace log file */
        FILE *trace;
        /* the http log file */
        FILE *http;
        /* the ws log file */
        FILE *ws;
        struct {
            size_t size;
            char **ids;
        } disable; /**< list of 'id' that should be ignored */
    } log; /**< logging directives */
};

/**
 * @brief Creates a Discord Client handle from a
 *      @ref discord_config structure
 * @see discord_get_logmod() to configure logging behavior
 *
 * @param config the @ref discord_config structure
 * @return the newly created Discord Client handle
 */
struct discord *discord_from_config(const struct discord_config *config);

/**
 * @brief Backwards compatible alias for discord_from_token()
 * @deprecated since v3.0.0
 */
#define discord_init discord_from_token

/**
 * @brief Backwards compatible alias for discord_from_json()
 * @deprecated since v3.0.0
 */
#define discord_config_init discord_from_json

/**
 * @brief Get the contents from the config file field
 * @note your bot **MUST** have been initialized with discord_from_json()
 *
 * @code{.c}
 * // Assume the following custom config.json field to be extracted
 * // "field": { "foo": "a string", "bar": 1234 }
 *
 * ...
 * struct ccord_szbuf_readonly value;
 * char foo[128];
 * long bar;
 *
 * // field.foo
 * value = discord_config_get_field(client, (char *[2]){ "field", "foo" }, 2);
 * snprintf(foo, sizeof(foo), "%.*s", (int)value.size, value.start);
 * // field.bar
 * value = discord_config_get_field(client, (char *[2]){ "field", "bar" }, 2);
 * bar = strtol(value.start, NULL, 10);
 *
 * printf("%s %ld", foo, bar); // "a string" 1234
 * @endcode
 *
 * @param client the client created with discord_from_json()
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
 * @param orig the original client created with discord_from_token()
 * @return the client clone
 */

struct discord *discord_clone(const struct discord *orig);

/**
 * @brief Free a Discord Client handle
 *
 * @param client the client created with discord_from_token()
 */

void discord_cleanup(struct discord *client);

/**
 * @brief Get the client's cached user
 *
 * @param client the client created with discord_from_token()
 * @warning the returned structure should NOT be modified
 */

const struct discord_user *discord_get_self(struct discord *client);

/**
 * @brief Start a connection to the Discord Gateway
 *
 * @param client the client created with discord_from_token()
 * @CCORD_return
 */
CCORDcode discord_run(struct discord *client);

/**
 * @brief Gracefully shutdown an ongoing Discord connection
 *
 * @param client the client created with discord_from_token()
 */
void discord_shutdown(struct discord *client);

/**
 * @brief Gracefully reconnects an ongoing Discord connection
 *
 * @param client the client created with discord_from_token()
 * @param resume true to attempt to resume to previous session,
 *        false restart a fresh session
 */
void discord_reconnect(struct discord *client, bool resume);

/**
 * @brief Store user arbitrary data that can be retrieved by discord_get_data()
 *
 * @param client the client created with discord_from_token()
 * @param data user arbitrary data
 * @return pointer to user data
 * @warning the user should provide their own locking mechanism to protect
 *        its data from race conditions
 */
void *discord_set_data(struct discord *client, void *data);

/**
 * @brief Receive user arbitrary data stored with discord_set_data()
 *
 * @param client the client created with discord_from_token()
 * @return pointer to user data
 * @warning the user should provide their own locking mechanism to protect
 *        its data from race conditions
 */
void *discord_get_data(struct discord *client);

/**
 * @brief Get the client WebSockets ping
 * @note Only works after a connection has been established via
 * discord_run()
 *
 * @param client the client created with discord_from_token()
 * @return the ping in milliseconds
 */
int discord_get_ping(struct discord *client);

/**
 * @brief Get the current timestamp (in milliseconds)
 *
 * @param client the client created with discord_from_token()
 * @return the timestamp in milliseconds
 */
uint64_t discord_timestamp(struct discord *client);

/**
 * @brief Get the current timestamp (in microseconds)
 *
 * @param client the client created with discord_from_token()
 * @return the timestamp in microseconds
 */
uint64_t discord_timestamp_us(struct discord *client);

/**
 * @brief Retrieve client's logging module for configuration purposes
 * @see logmod.h
 *
 * @param client the client created with discord_from_token()
 * @return the client's logging manager
 */
struct logmod *discord_get_logmod(struct discord *client);

/**
 * @brief get the io_poller used by the discord client
 *
 * @param client the client created with discord_from_token()
 * @return struct io_poller*
 */
struct io_poller *discord_get_io_poller(struct discord *client);

/** @addtogroup DiscordTimer Timer
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
    /** flag is set when on_tick callback has been called */
    DISCORD_TIMER_TICK = 1 << 4,
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
    /** (nullable) the callback that should be called when timer triggers */
    discord_ev_timer on_tick;
    /** (nullable) the callback for status updates timer->flags
     * will have: DISCORD_TIMER_CANCELED, and DISCORD_TIMER_DELETE */
    discord_ev_timer on_status_changed;
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
 * @param client the client created with discord_from_token()
 * @param timer the timer that should be modified
 * @return the id of the timer
 */
unsigned discord_timer_ctl(struct discord *client,
                           struct discord_timer *timer);

/**
 * @brief creates a one shot timer that automatically
 *        deletes itself upon completion
 *
 * @param client the client created with discord_from_token()
 * @param on_tick_cb (nullable) the callback that should be called when timer
 * triggers
 * @param on_status_changed_cb (nullable) the callback for status updates
 * timer->flags will have: DISCORD_TIMER_CANCELED, and DISCORD_TIMER_DELETE
 * @param data user data
 * @param delay delay before timer should start in milliseconds
 * @return the id of the timer
 */
unsigned discord_timer(struct discord *client,
                       discord_ev_timer on_tick_cb,
                       discord_ev_timer on_status_changed_cb,
                       void *data,
                       int64_t delay);

/**
 * @brief creates a repeating timer that automatically
 *        deletes itself upon completion
 *
 * @param client the client created with discord_from_token()
 * @param on_tick_cb (nullable) the callback that should be called when timer
 * triggers
 * @param on_status_changed_cb (nullable) the callback for status updates
 * timer->flags will have: DISCORD_TIMER_CANCELED, and DISCORD_TIMER_DELETE
 * @param data user data
 * @param delay delay before timer should start in milliseconds
 * @param interval interval between runs. (-1 == disable repeat)
 * @param repeat repetitions (-1 == infinity)
 * @return the id of the timer
 */
unsigned discord_timer_interval(struct discord *client,
                                discord_ev_timer on_tick_cb,
                                discord_ev_timer on_status_changed_cb,
                                void *data,
                                int64_t delay,
                                int64_t interval,
                                int64_t repeat);

/**
 * @brief get the data associated with the timer
 *
 * @param client the client created with discord_from_token()
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
 * @param client the client created with discord_from_token()
 * @param id id of the timer
 * @return true on success
 */
bool discord_timer_start(struct discord *client, unsigned id);

/**
 * @brief stops a timer
 *
 * @param client the client created with discord_from_token()
 * @param id id of the timer
 * @return true on success
 */
bool discord_timer_stop(struct discord *client, unsigned id);

/**
 * @brief cancels a timer,
 * this will delete the timer if DISCORD_TIMER_DELETE_AUTO is enabled
 *
 * @param client the client created with discord_from_token()
 * @param id id of the timer
 * @return true on success
 */
bool discord_timer_cancel(struct discord *client, unsigned id);

/**
 * @brief deletes a timer
 *
 * @param client the client created with discord_from_token()
 * @param id id of the timer
 * @return true on success
 */
bool discord_timer_delete(struct discord *client, unsigned id);

/**
 * @brief cancels, and deletes a timer
 *
 * @param client the client created with discord_from_token()
 * @param id id of the timer
 * @return true on success
 */
bool discord_timer_cancel_and_delete(struct discord *client, unsigned id);

/** @example timers.c
 * Demonstrates the Timer API for callback scheduling */

/** @} DiscordTimer */
/** @} DiscordClient */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DISCORD_H */
