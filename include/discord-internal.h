/**
 * @file discord-internal.h
 * @ingroup DiscordInternal
 * @author Cogmasters
 * @brief Internal functions and datatypes
 */

#ifndef DISCORD_INTERNAL_H
#define DISCORD_INTERNAL_H

#include <inttypes.h>
#include <pthread.h>

#define JSONB_HEADER
#include "json-build.h"
#define JSMN_STRICT
#define JSMN_HEADER
#include "jsmn.h"
#include "jsmn-find.h"

#include "logconf.h" /* struct logconf */
#include "user-agent.h"
#include "websockets.h"
#include "work.h"
#include "cog-utils.h"
#include "io_poller.h"

#include "uthash.h"
#include "queue.h"
#include "priority_queue.h"

/** @brief Return 1 if string isn't considered empty */
#define NOT_EMPTY_STR(str) ((str) && *(str))
/**
 * @brief Get container `type` from a field `ptr`
 *
 * @param ptr the field contained in `type`
 * @param type the container datatype
 * @param path the path to the field from the container POV
 */
#define CONTAINEROF(ptr, type, path)                                          \
    ((type *)((char *)(ptr)-offsetof(type, path)))

/** @defgroup DiscordInternal Internal implementation details
 * @brief Documentation useful when developing or debugging Concord itself
 *  @{ */

/** @brief Get client from its nested field */
#define CLIENT(ptr, path) CONTAINEROF(ptr, struct discord, path)

/**
 * @brief log and return `code` if `expect` condition is false
 *
 * @param expect the expected outcome
 * @param client the discord client
 * @param error return CCORDcode error
 * @param reason for return
 */
#define CCORD_EXPECT(client, expect, code, reason)                            \
    do {                                                                      \
        if (!(expect)) {                                                      \
            logconf_error(&(client)->conf, "Expected: " #expect ": " reason); \
            return code;                                                      \
        }                                                                     \
    } while (0)

/**
 * @brief Shortcut for checking OOB-write attempts
 * @note unsigned values are expected
 *
 * @param nbytes amount of bytes to be written
 * @param destsz size of dest in bytes
 */
#define ASSERT_NOT_OOB(nbytes, destsz)                                        \
    ASSERT_S((size_t)nbytes < (size_t)destsz, "Out of bounds write attempt");

/** @defgroup DiscordInternalAdapter REST API
 * @brief Wrapper to the Discord REST API
 *  @{ */

/** @brief Request's return context */
struct discord_ret_generic {
    /** `true` if may receive a datatype from response*/
    bool has_type;

    /** optional callback to be executed on a successful request */
    union {
        void (*typed)(struct discord *client, void *data, const void *ret);
        void (*typeless)(struct discord *client, void *data);
    } done;

    DISCORDT_RET_DEFAULT_FIELDS;

    /** if an address is provided, then request will block the thread and
     * perform on-spot. On success the response object will be written to
     * the address. */
    void *sync;
};

/** @brief Attributes of response datatype */
struct discord_generic {
    /** pointer to the datatype in memory */
    void *data;
    /** size of datatype in bytes */
    size_t size;
    /** initializer function for datatype fields */
    void (*init)(void *data);
    /** populate datatype with JSON values */
    size_t (*from_json)(const char *json, size_t len, void *data);
    /** cleanup function for datatype */
    void (*cleanup)(void *data);
};

/** @brief Behavior of request return struct */
struct discord_request {
    /** request response's return datatype attributes */
    struct discord_generic gnrc;
    /** request attributes set by client */
    struct discord_ret_generic ret;
    /** in case of HTTP_MIMEPOST, provide attachments */
    struct discord_attachments attachments;
};

/** URL endpoint threshold length */
#define DISCORD_ENDPT_LEN 512
/** Bucket's route threshold length */
#define DISCORD_ROUTE_LEN 256

/**
 * @brief Context of individual requests that are scheduled to run
 *        asynchronously
 */
struct discord_context {
    /** request return struct attributes */
    struct discord_request req;

    /** the request's bucket */
    struct discord_bucket *bucket;

    /** request body handle @note buffer is kept and recycled */
    struct {
        /** the request body contents */
        struct sized_buffer buf;
        /** the real size occupied in memory by `buf.start` */
        size_t memsize;
    } body;

    /** the request's http method */
    enum http_method method;
    /** the request's endpoint */
    char endpoint[DISCORD_ENDPT_LEN];
    /** the request's route */
    char route[DISCORD_ROUTE_LEN];
    /** the connection handler assigned */
    struct ua_conn *conn;
    /** the request bucket's queue entry */
    QUEUE entry;

    /** current retry attempt (stop at adapter->retry_limit) */
    int retry_attempt;
};

/** @brief The handle used for performing HTTP Requests */
struct discord_adapter {
    /** DISCORD_HTTP or DISCORD_WEBHOOK logging module */
    struct logconf conf;
    /** the user agent handle for performing requests */
    struct user_agent *ua;
    /** curl_multi handle for performing non-blocking requests */
    CURLM *mhandle;
    /** client-side data reference counter for cleanup */
    struct discord_refcount *refcounts;
    /** routes discovered (declared at adapter-ratelimit.c) */
    struct _discord_route *routes;
    /** buckets discovered */
    struct discord_bucket *buckets;
    /** for routes that have not yet been assigned to a bucket */
    struct discord_bucket *b_null;
    /** for routes didn't receive a bucket match from Discord */
    struct discord_bucket *b_miss;

    /* client-wide ratelimiting timeout */
    struct {
        /** global ratelimit */
        u64unix_ms wait_ms;
        /** global rwlock  */
        pthread_rwlock_t rwlock;
        /** global lock */
        pthread_mutex_t lock;
    } * global;

    /** idle request handles */
    QUEUE(struct discord_context) * idleq;

    /** max amount of retries before a failed request gives up */
    int retry_limit;
};

/**
 * @brief Initialize the fields of a Discord Adapter handle
 *
 * @param adapter a pointer to the http handle
 * @param conf optional pointer to a pre-initialized logconf
 * @param token the bot token
 */
void discord_adapter_init(struct discord_adapter *adapter,
                          struct logconf *conf,
                          struct sized_buffer *token);

/**
 * @brief Free a Discord Adapter handle
 *
 * @param adapter the handle initialized with discord_adapter_init()
 */
void discord_adapter_cleanup(struct discord_adapter *adapter);

/**
 * @brief Perform a request to Discord
 *
 * This functions is a selector over discord_adapter_run() or
 *        discord_adapter_run_async()
 * @param adapter the handle initialized with discord_adapter_init()
 * @param req return object of request
 * @param body the body sent for methods that require (ex: post), leave as
 *        null if unecessary
 * @param method the method in opcode format of the request being sent
 * @param endpoint_fmt the printf-like endpoint formatting string
 * @CCORD_return
 * @note if sync is set then this function will block the thread and perform it
 *              immediately
 */
CCORDcode discord_adapter_run(struct discord_adapter *adapter,
                              struct discord_request *req,
                              struct sized_buffer *body,
                              enum http_method method,
                              char endpoint_fmt[],
                              ...);

/**
 * @brief Check and manage on-going, pending and timed-out requests
 *
 * @param adapter the handle initialized with discord_adapter_init()
 * @CCORD_return
 */
CCORDcode discord_adapter_perform(struct discord_adapter *adapter);

/**
 * @brief Get global timeout timestamp
 *
 * @param adapter the handle initialized with discord_adapter_init()
 * @return the most recent global timeout timestamp
 */
u64unix_ms discord_adapter_get_global_wait(struct discord_adapter *adapter);

/**
 * @brief Stop all on-going, pending and timed-out requests
 *
 * The requests will be moved over to client's 'idleq' queue
 * @param adapter the handle initialized with discord_adapter_init()
 */
void discord_adapter_stop_all(struct discord_adapter *adapter);

/** @brief Naive garbage collector to cleanup user arbitrary data */
struct discord_refcount {
    /** user arbitrary data to be retrieved at `done` or `fail` callbacks */
    void *data;
    /**
     * cleanup for when `data` is no longer needed
     * @note this only has to be assigned once, it shall be called once `data`
     *      is no longer referenced by any callback */
    void (*cleanup)(void *data);
    /** `data` references count */
    int visits;
    /** makes this structure hashable */
    UT_hash_handle hh;
};

/**
 * @brief Increment the reference counter for `ret->data`
 *
 * @param adapter the handle initialized with discord_adapter_init()
 * @param data the user arbitrary data to have its reference counter
 * @param cleanup user-defined function for cleaning `data` resources once its
 *      no longer referenced
 */
void discord_refcount_incr(struct discord_adapter *adapter,
                           void *data,
                           void (*cleanup)(void *data));

/**
 * @brief Decrement the reference counter for `data`
 *
 * If the count reaches zero then `data` shall be cleanup up with its
 *      user-defined cleanup function
 * @param adapter the handle initialized with discord_adapter_init()
 * @param data the user arbitrary data to have its reference counter
 *      decremented
 */
void discord_refcount_decr(struct discord_adapter *adapter, void *data);

/** @defgroup DiscordInternalAdapterRatelimit Ratelimiting
 * @brief Enforce ratelimiting per the official Discord Documentation
 *  @{ */

/** @brief The bucket struct for handling ratelimiting */
struct discord_bucket {
    /** the hash associated with this bucket */
    char hash[64];
    /** maximum connections this bucket can handle before ratelimit */
    long limit;
    /** connections this bucket can do before waiting for cooldown */
    long remaining;
    /** timestamp of when cooldown timer resets */
    u64unix_ms reset_tstamp;
    /** synchronize ratelimiting between threads */
    pthread_mutex_t lock;
    /** pending requests */
    QUEUE(struct discord_context) waitq;
    /** busy requests */
    QUEUE(struct discord_context) busyq;
    /** makes this structure hashable */
    UT_hash_handle hh;
};

/**
 * @brief Initialize a individual bucket and assign it to `adapter`
 *
 * @param adapter the handle initialized with discord_adapter_init()
 * @param hash the bucket's hash (for identification purposes)
 * @param limit the bucket's request threshold
 */
struct discord_bucket *discord_bucket_init(struct discord_adapter *adapter,
                                           const struct sized_buffer *hash,
                                           const long limit);

/**
 * @brief Cleanup all buckets allocated
 *
 * @param adapter the handle initialized with discord_adapter_init()
 */
void discord_buckets_cleanup(struct discord_adapter *adapter);

/**
 * @brief Return bucket timeout timestamp
 *
 * @param adapter the handle initialized with discord_adapter_init()
 * @param b the bucket to be checked for time out
 * @return the timeout timestamp
 */
u64unix_ms discord_bucket_get_timeout(struct discord_adapter *adapter,
                                      struct discord_bucket *b);

/**
 * @brief Get bucket pending cooldown time in milliseconds
 *
 * @param adapter the handle initialized with discord_adapter_init()
 * @param the bucket to wait on cooldown
 * @return amount to sleep for in milliseconds
 */
int64_t discord_bucket_get_wait(struct discord_adapter *adapter,
                                struct discord_bucket *bucket);

/**
 * @brief Get `route` from HTTP method and endpoint
 *
 * @param method the request method
 * @param route buffer filled with generated route
 * @param endpoint_fmt the printf-like endpoint formatting string
 * @param args variadic arguments matched to `endpoint_fmt`
 */
void discord_bucket_get_route(enum http_method method,
                              char route[DISCORD_ROUTE_LEN],
                              const char endpoint_fmt[],
                              va_list args);

/**
 * @brief Get a `struct discord_bucket` assigned to `route`
 *
 * @param adapter the handle initialized with discord_adapter_init()
 * @param route route obtained from discord_bucket_get_route()
 * @return bucket assigned to `route` or `adapter->b_null` if no match found
 */
struct discord_bucket *discord_bucket_get(struct discord_adapter *adapter,
                                          const char route[DISCORD_ROUTE_LEN]);

/**
 * @brief Update the bucket with response header data
 *
 * @param adapter the handle initialized with discord_adapter_init()
 * @param bucket NULL when bucket is first discovered
 * @param route route obtained from discord_bucket_get_route()
 * @param info informational struct containing details on the current transfer
 * @note If the bucket was just discovered it will be created here.
 */
void discord_bucket_build(struct discord_adapter *adapter,
                          struct discord_bucket *bucket,
                          const char route[DISCORD_ROUTE_LEN],
                          struct ua_info *info);

/** @} DiscordInternalAdapterRatelimit */

/** @} DiscordInternalAdapter */

/** @defgroup DiscordInternalGateway WebSockets API
 * @brief Wrapper to the Discord Gateway API
 *  @{ */

struct discord_gateway_cbs {
    /** triggers when connection first establishes */
    discord_ev_idle on_ready;

    /** triggers when a command is created */
    discord_ev_application_command on_application_command_create;
    /** triggers when a command is updated */
    discord_ev_application_command on_application_command_update;
    /** triggers when a command is deleted */
    discord_ev_application_command on_application_command_delete;

    /** triggers when a channel is created */
    discord_ev_channel on_channel_create;
    /** triggers when a channel is updated */
    discord_ev_channel on_channel_update;
    /** triggers when a channel is deleted */
    discord_ev_channel on_channel_delete;
    /** triggers when a channel pinned messages updates */
    discord_ev_channel_pins_update on_channel_pins_update;
    /** triggers when a thread is created */
    discord_ev_channel on_thread_create;
    /** triggers when a thread is updated */
    discord_ev_channel on_thread_update;
    /** triggers when a thread is deleted */
    discord_ev_channel on_thread_delete;

    /** triggers when guild info is ready, or a guild has joined */
    discord_ev_guild on_guild_create;
    /** triggers when a guild's information is updated */
    discord_ev_guild on_guild_update;
    /** triggers when removed from guild */
    discord_ev_guild_delete on_guild_delete;

    /** triggers when a ban occurs */
    discord_ev_guild_ban on_guild_ban_add;
    /** triggers when a ban is removed */
    discord_ev_guild_ban on_guild_ban_remove;

    /** triggers when a guild member joins a guild */
    discord_ev_guild_member on_guild_member_add;
    /** triggers when a guild member is removed from a guild */
    discord_ev_guild_member_remove on_guild_member_remove;
    /** triggers when a guild member status is updated (ex: receive role) */
    discord_ev_guild_member on_guild_member_update;

    /** triggers when a guild role is created */
    discord_ev_guild_role on_guild_role_create;
    /** triggers when a guild role is updated */
    discord_ev_guild_role on_guild_role_update;
    /** triggers when a guild role is deleted */
    discord_ev_guild_role_delete on_guild_role_delete;

    /** triggers when a interaction is created  */
    discord_ev_interaction on_interaction_create;

    /** triggers when a message is created */
    discord_ev_message on_message_create;
    /** trigger when a message is updated */
    discord_ev_message on_message_update;
    /** triggers when a message is deleted */
    discord_ev_message_delete on_message_delete;
    /** triggers when a bulk of messages is deleted */
    discord_ev_message_delete_bulk on_message_delete_bulk;
    /** triggers when a reaction is added to a message */
    discord_ev_message_reaction_add on_message_reaction_add;
    /** triggers when a reaction is removed from a message */
    discord_ev_message_reaction_remove on_message_reaction_remove;
    /** triggers when all reactions are removed from a message */
    discord_ev_message_reaction_remove_all on_message_reaction_remove_all;
    /** triggers when all occurences of a specific reaction is removed from a
     * message */
    discord_ev_message_reaction_remove_emoji on_message_reaction_remove_emoji;

    /** triggers when a voice state is updated */
    discord_ev_voice_state_update on_voice_state_update;
    /** triggers when a voice server is updated */
    discord_ev_voice_server_update on_voice_server_update;
};

/** @defgroup DiscordInternalGatewaySessionStatus Client's session status
 * @brief Client's session status
 *  @{ */
/** client is currently offline */
#define DISCORD_SESSION_OFFLINE 0u
/** client will attempt to resume session after reconnect */
#define DISCORD_SESSION_RESUMABLE 1u << 0
/** client in the process of being shutdown */
#define DISCORD_SESSION_SHUTDOWN 1u << 1
/** @} DiscordInternalGatewaySessionStatus */

/** @brief The handle used for establishing a WebSockets connection */
struct discord_gateway {
    /** DISCORD_GATEWAY logging module */
    struct logconf conf;
    /** the websockets handle that connects to Discord */
    struct websockets *ws;
    /** curl_multi handle for non-blocking transfer over websockets */
    CURLM *mhandle;

    /** timers kept for synchronization */
    struct {
        /** fixed interval between heartbeats */
        u64unix_ms interval;
        /** last heartbeat pulse timestamp */
        u64unix_ms hbeat;
        /** Gateway's concept of "now" */
        u64unix_ms now;
        /** timestamp of last succesful identify request */
        u64unix_ms identify;
        /** timestamp of last succesful event timestamp in ms (resets every
         * 60s) */
        u64unix_ms event;
        /** latency obtained from HEARTBEAT and HEARTBEAT_ACK interval */
        int ping_ms;
        /** ping rwlock  */
        pthread_rwlock_t rwlock;
    } * timer;

    /** the identify structure for client authentication */
    struct discord_identify id;

    /** on-going session structure */
    struct {
        /** whether client is ready to start sending/receiving events */
        bool is_ready;
        /** session id for resuming lost connections */
        char id[64];
        /** amount of shards being used by this session */
        int shards;
        /** session limits */
        struct discord_session_start_limit start_limit;
        /** active concurrent sessions */
        int concurrent;
        /** event counter to avoid reaching limit of 120 events per 60 sec */
        int event_count;
        /** @ref DiscordInternalGatewaySessionStatus */
        unsigned status;

        /** retry connection structure */
        struct {
            /** will attempt reconnecting if true */
            bool enable;
            /** current retry attempt (resets to 0 when succesful) */
            int attempt;
            /** max amount of retries before giving up */
            int limit;
        } retry;
    } * session;

    /**
     * parse JSON tokens into a `jsmnf_pairs` key/value pairs hashtable
     * @todo store pairs and tokens 'realsize' to avoid unecessarily performing
     *      realloc memory "decreases" (i.e only realloc when increasing is
     *      necessary)
     */
    struct {
        /** current iteration JSON key/value pairs */
        jsmnf_pair *pairs;
        /** current iteration number of JSON key/value pairs */
        unsigned npairs;
        /** current iteration JSON tokens (fed to `jsmnf_pair`) */
        jsmntok_t *tokens;
        /** current iteration number of JSON tokens */
        unsigned ntokens;
    } parse;

    /** response-payload structure */
    struct {
        /** field 'op' */
        enum discord_gateway_opcodes opcode;
        /** field 's' */
        int seq;
        /** field 't' */
        char name[32];
        /** field 'd' @deprecated replaced with `_data` */
        struct sized_buffer data;
        /** field 'd' */
        jsmnf_pair *_data;
    } payload;

    /** user-commands structure */
    struct {
        /** the prefix expected for every command */
        struct sized_buffer prefix;
        /** user's command/callback pair @see discord_set_on_command() */
        struct {
            /** the command string contents */
            char *start;
            /** the command string length */
            size_t size;
            /** the assigned callback for the command */
            discord_ev_message cb;
        } * pool, fallback;
        /** amount of command/callback pairs in pool */
        size_t amt;
        /** actual size of command/callback pairs in pool */
        size_t cap;

        /** the user's callbacks for Discord events */
        struct discord_gateway_cbs cbs;
        /** the event scheduler callback */
        discord_ev_scheduler scheduler;
    } cmds;
};

/**
 * @brief Context in case event is scheduled to be triggered
 *        from concord's worker threads
 */
struct discord_event {
    /** the event name */
    char *name;
    /** a copy of payload data */
    struct sized_buffer data;
    /** the discord gateway client */
    struct discord_gateway *gw;
    /** the event unique id value */
    enum discord_gateway_events event;
    /** the event callback */
    void (*on_event)(struct discord_gateway *gw);
};

/**
 * @brief Initialize the fields of Discord Gateway handle
 *
 * @param gw the gateway handle to be initialized
 * @param conf optional pointer to a initialized logconf
 * @param token the bot token
 */
void discord_gateway_init(struct discord_gateway *gw,
                          struct logconf *conf,
                          struct sized_buffer *token);

/**
 * @brief Free a Discord Gateway handle
 *
 * @param gw the handle initialized with discord_gateway_init()
 */
void discord_gateway_cleanup(struct discord_gateway *gw);

/**
 * @brief Initialize handle with the new session primitives
 *
 * @param gw the handle initialized with discord_gateway_init()
 * @CCORD_return
 */
CCORDcode discord_gateway_start(struct discord_gateway *gw);

/**
 * @brief Cleanup and reset `gw` session primitives
 *
 * @param ws the WebSockets handle created with ws_init()
 * @return `true` if session is over, `false` if session can be retried for
 *      reconnection
 */
bool discord_gateway_end(struct discord_gateway *gw);

/**
 * @brief Check and manage on-going Gateway session
 *
 * @param req the request handler
 * @CCORD_return
 */
CCORDcode discord_gateway_perform(struct discord_gateway *gw);

/**
 * @brief Gracefully shutdown a ongoing Discord connection over WebSockets
 *
 * @param gw the handle initialized with discord_gateway_init()
 */
void discord_gateway_shutdown(struct discord_gateway *gw);

/**
 * @brief Gracefully reconnect a ongoing Discord connection over WebSockets
 *
 * @param gw the handle initialized with discord_gateway_init()
 * @param resume true to attempt to resume to previous session,
 *        false restart a fresh session
 */
void discord_gateway_reconnect(struct discord_gateway *gw, bool resume);

/**
 * @brief Send client's presence status update payload
 *
 * @param gw the handle initialized with discord_gateway_init()
 */
void discord_gateway_send_presence_update(struct discord_gateway *gw);

/** @} DiscordInternalGateway */

/** @defgroup DiscordInternalTimer Timer API
 * @brief Callback scheduling API
 *  @{ */

struct discord_timers {
    priority_queue *q;
    struct discord_timer *currently_being_run;
};

/**
 * @brief prepare timers for usage
 *
 * @param client the client created with discord_init()
 */
void discord_timers_init(struct discord *client);

/**
 * @brief cleanup timers and call cancel any running ones
 *
 * @param client the client created with discord_init()
 */
void discord_timers_cleanup(struct discord *client);

/**
 * @brief run all timers that are due
 *
 * @param client the client created with discord_init()
 * @param timers the timers to run
 */
void discord_timers_run(struct discord *client, struct discord_timers *timers);

/**
 * @brief modifies or creates a timer
 *
 * @param client the client created with discord_init()
 * @param timers the timer group to perform this operation on
 * @param timer the timer that should be modified
 * @return the id of the timer
 */
unsigned _discord_timer_ctl(struct discord *client,
                            struct discord_timers *timers,
                            struct discord_timer *timer);

/**
 * @brief modifies or creates a timer
 *
 * @param client the client created with discord_init()
 * @param timer the timer that should be modified
 * @return unsigned the id of the timer
 */
unsigned discord_internal_timer_ctl(struct discord *client,
                                    struct discord_timer *timer);

/**
 * @brief creates a one shot timer that automatically
 *        deletes itself upon completion
 *
 * @param client the client created with discord_init()
 * @param cb the callback that should be called when timer triggers
 * @param data user data
 * @param delay delay before timer should start in milliseconds
 * @return unsigned
 */
unsigned discord_internal_timer(struct discord *client,
                                discord_ev_timer cb,
                                void *data,
                                int64_t delay);

/** @} DiscordInternalTimer */
/**
 * @brief The Discord client handler
 *
 * Used to access/perform public functions from discord.h
 * @see discord_init(), discord_config_init(), discord_cleanup()
 */
struct discord {
    /** DISCORD logging module */
    struct logconf conf;
    /** whether this is the original client or a clone @deprecated unnecessary
     *      once discord_clone() is removed */
    bool is_original;
    /** the bot token */
    struct sized_buffer token;
    /** the io poller for listening to file descriptors */
    struct io_poller *io_poller;
    /** the HTTP adapter for performing requests */
    struct discord_adapter adapter;
    /** the WebSockets handle for establishing a connection to Discord */
    struct discord_gateway gw;
    /** the client's user structure */
    struct discord_user self;

    struct {
        struct discord_timers internal;
        struct discord_timers user;
    } timers;

    /** wakeup timer handle */
    struct {
        /** callback to be triggered on timer's timeout */
        discord_ev_idle cb;
        /** the id of the wake timer */
        unsigned id;
    } wakeup_timer;

    /** triggers when idle.  */
    discord_ev_idle on_idle;
    /** triggers once per loop cycle */
    discord_ev_idle on_cycle;

    /** space for user arbitrary data */
    void *data;

#ifdef CCORD_VOICE
    struct discord_voice vcs[DISCORD_MAX_VCS];
    struct discord_voice_cbs voice_cbs;
#endif /* CCORD_VOICE */
};

/** @} DiscordInternal */

#endif /* DISCORD_INTERNAL_H */
