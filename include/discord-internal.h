/**
 * @file discord-internal.h
 * @ingroup DiscordInternal
 * @author Cogmasters
 * @brief Internal functions and datatypes
 */

#ifndef DISCORD_INTERNAL_H
#define DISCORD_INTERNAL_H

#include <pthread.h>

#define JSONB_HEADER
#include "json-build.h"
#define JSMN_STRICT
#define JSMN_HEADER
#include "jsmn.h"
#include "jsmn-find.h"

#include "logconf.h"
#include "user-agent.h"
#include "websockets.h"
#include "work.h"
#include "cog-utils.h"
#include "io_poller.h"

#include "queue.h"
#include "priority_queue.h"

/** @brief Return 1 if string isn't considered empty */
#define NOT_EMPTY_STR(str) ((str) && *(str))
/**
 * @brief Get container `type` from a field `ptr`
 *
 * @param[in] ptr the field contained in `type`
 * @param[in] type the container datatype
 * @param[in] path the path to the field from the container POV
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
 * @param[in] client the Discord client
 * @param[in] expect the expected outcome
 * @param[in] code return CCORDcode error code
 * @param[in] reason for return
 * @return the provided @ref CCORDcode `code` parameter
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
 * @param[in] nbytes amount of bytes to be written
 * @param[in] destsz size of dest in bytes
 */
#define ASSERT_NOT_OOB(nbytes, destsz)                                        \
    ASSERT_S((size_t)nbytes < (size_t)destsz, "Out of bounds write attempt");

/** URL endpoint threshold length */
#define DISCORD_ENDPT_LEN 512
/** Route's unique key threshold length */
#define DISCORD_ROUTE_LEN 256

/** @defgroup DiscordInternalTimer Timer API
 * @brief Callback scheduling API
 *  @{ */

struct discord_timers {
    priority_queue *q;
    struct {
        struct discord_timer *timer;
        bool skip_update_phase;
    } active;
};

/**
 * @brief Prepare timers for usage
 *
 * @param timers the 'struct discord_timers' to init
 */
void discord_timers_init(struct discord_timers *timers);

/**
 * @brief Cleanup timers and call cancel any running ones
 *
 * @param client the client created with discord_init()
 * @param timers the 'struct discord_timers' to cleanup
 */
void discord_timers_cleanup(struct discord *client,
                            struct discord_timers *timers);

/**
 * @brief Get earliest trigger time from a group of timers
 *
 * @param timers array of timers
 * @param n number of timers in array
 * @param now current time
 * @param max_time max time to allowed
 * @return time in microseconds until next timer, or max
 */
int64_t discord_timers_get_next_trigger(struct discord_timers *const timers[],
                                        size_t n,
                                        int64_t now,
                                        int64_t max_time);

/**
 * @brief Run all timers that are due
 *
 * @param client the client created with discord_init()
 * @param timers the timers to run
 */
void discord_timers_run(struct discord *client, struct discord_timers *timers);

/**
 * @brief Modifies or creates a timer
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
 * @brief Modifies or creates a timer
 *
 * @param client the client created with discord_init()
 * @param timer the timer that should be modified
 * @return the id of the timer
 */
unsigned discord_internal_timer_ctl(struct discord *client,
                                    struct discord_timer *timer);

/**
 * @brief Creates a one shot timer that automatically deletes itself upon
 *      completion
 *
 * @param client the client created with discord_init()
 * @param cb the callback that should be called when timer triggers
 * @param data user data
 * @param delay delay before timer should start in milliseconds
 * @return the id of the timer
 */
unsigned discord_internal_timer(struct discord *client,
                                discord_ev_timer cb,
                                void *data,
                                int64_t delay);

/** @} DiscordInternalTimer */

/** @defgroup DiscordInternalREST REST API
 * @brief Wrapper to the Discord REST API
 *  @{ */

/** @brief Generic request dispatcher */
struct discord_ret_dispatch {
    DISCORD_RET_DEFAULT_FIELDS;
    /** `true` if may receive a datatype from response */
    bool has_type;

    /**
     * optional callback to be executed on a successful request
     * @todo should be cast to the original callback signature before calling,
     *      otherwise its UB
     */
    union {
        void (*typed)(struct discord *client,
                      struct discord_response *resp,
                      const void *ret);
        void (*typeless)(struct discord *client,
                         struct discord_response *resp);
    } done;

    /** if an address is provided, then request will block the thread and
     * perform on-spot. On success the response object will be written to
     * the address. */
    void *sync;
};

/** @brief Attributes of response datatype */
struct discord_ret_response {
    /** pointer to datatype */
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

/**
 * @brief Macro containing @ref discord_request fields
 * @note this exists for @ref discord_context alignment purposes
 */
#define DISCORD_REQUEST_FIELDS                                                \
    /** attributes set by client for request dispatch behavior */             \
    struct discord_ret_dispatch dispatch;                                     \
    /** information for parsing response into a datatype (if possible) */     \
    struct discord_ret_response response;                                     \
    /** in case of `HTTP_MIMEPOST` provide attachments for file transfer */   \
    struct discord_attachments attachments

/** @brief Request to be performed */
struct discord_request {
    DISCORD_REQUEST_FIELDS;
};

/** @defgroup DiscordInternalRESTAsync Async request's handling
 * @brief Store contexts of individual asynchronous requests
 *  @{ */

/**
 * @brief Context of individual requests that are scheduled to run
 *      asynchronously
 * @note its fields are aligned with @ref discord_request
 */
struct discord_context {
    DISCORD_REQUEST_FIELDS;

    /** the request's bucket */
    struct discord_bucket *b;
    /** request body handle @note buffer is kept and reused */
    struct ccord_szbuf_reusable body;
    /** the request's http method */
    enum http_method method;
    /** the request's endpoint */
    char endpoint[DISCORD_ENDPT_LEN];
    /** the request bucket's key */
    char key[DISCORD_ROUTE_LEN];
    /** the connection handler assigned */
    struct ua_conn *conn;

    /** current retry attempt (stop at rest->retry_limit) */
    int retry_attempt;
    /** the request bucket's queue entry */
    QUEUE entry;
    /** synchronize synchronous requests */
    pthread_cond_t *cond;
};

/** @brief The handle used for handling asynchronous requests */
struct discord_async {
    /** DISCORD_ASYNC logging module */
    struct logconf conf;
    /** curl_multi handle for performing asynchronous requests */
    CURLM *mhandle;
    /** io_poller for rest only */
    struct io_poller *io_poller;

    /** context queues */
    struct {
        /** requests contexts for recycling */
        QUEUE(struct discord_context) recycling;
        /**
         * finished requests contexts that are done performing and waiting for
         *      their callbacks to be called from the main thread
         */
        QUEUE(struct discord_context) finished;
    } * queues;
};

/**
 * @brief Initialize an Async handle
 *
 * This shall initialize a `CURLM` multi handle for performing requests
 *      asynchronously, and a queue for storing individual requests contexts
 * @param async the async handle to be initialized
 * @param conf pointer to @ref discord_rest logging module
 */
void discord_async_init(struct discord_async *async, struct logconf *conf);

/**
 * @brief Free an Async handle
 *
 * @param async the handle initialized with discord_async_init()
 */
void discord_async_cleanup(struct discord_async *async);

/**
 * @brief Kickstart the request by adding it to libcurl's request multiplexer
 *      (`CURLM` multi handle)
 *
 * @param async the async handle initialized with discord_async_init()
 * @param cxt the context of the request to be sent over
 * @param conn the @ref ua_conn connection handle
 * @return CCORDcode for how the request went, @ref CCORD_CURLM_INTERNAL means
 *      something wrong happened
 */
CCORDcode discord_async_add_request(struct discord_async *async,
                                    struct discord_context *cxt,
                                    struct ua_conn *conn);

/**
 * @brief Request failed, enqueue it back to bucket's first position
 *      for next attempt
 *
 * @param async the async handle initialized with discord_async_init()
 * @param cxt the failed request's context to be set for retry
 * @param wait_ms in case of a @ref HTTP_TOO_MANY_REQUESTS, this is the
 *      ratelimiting time to wait for
 * @return `true` if request can be retried
 */
bool discord_async_retry_context(struct discord_async *async,
                                 struct discord_context *cxt,
                                 int64_t wait_ms);

/**
 * @brief Insert a @ref discord_context structure into
 *      `async.queues->recycling` queue for recycling
 *
 * @param async the async handle initialized with discord_async_init()
 * @param cxt the request context to be recycled
 */
void discord_async_recycle_context(struct discord_async *async,
                                   struct discord_context *cxt);

/**
 * @brief Start request's context
 *
 * @param async the async handle initialized with discord_async_init()
 * @param req the request containing preliminary information for its dispatch
 * and response's parsing
 * @param body the request's body
 * @param method the request's HTTP method
 * @param endpoint the request's endpoint
 * @param key the request bucket's group for ratelimiting
 * @return the initialized request context
 */
struct discord_context *discord_async_start_context(
    struct discord_async *async,
    struct discord_request *req,
    struct ccord_szbuf *body,
    enum http_method method,
    char endpoint[DISCORD_ENDPT_LEN],
    char key[DISCORD_ROUTE_LEN],
    struct discord_bucket *b);

/** @} DiscordInternalRESTAsync */

/** @defgroup DiscordInternalRESTRatelimit Ratelimiting
 * @brief Enforce ratelimiting per the official Discord Documentation
 *  @{ */

/**
 * @brief Value assigned to @ref discord_bucket `pending_cxt` field in case
 *      it's being timed-out
 */
#define DISCORD_BUCKET_TIMEOUT (void *)(0xf)

/** @brief The ratelimiter struct for handling ratelimiting */
struct discord_ratelimiter {
    /** DISCORD_RATELIMIT logging module */
    struct logconf conf;
    /** amount of bucket's routes discovered */
    int length;
    /** route's cap before increase */
    int capacity;
    /**
     * routes matched to individual buckets
     * @note datatype declared at discord-rest_ratelimit.c
     */
    struct _discord_route *routes;
    /** singleton bucket for requests that haven't been matched to a
     *      known or new bucket (i.e first time running the request) */
    struct discord_bucket *null;
    /** singleton bucket for requests that are not part of any known
     *      ratelimiting group */
    struct discord_bucket *miss;

    /* client-wide ratelimiting timeout */
    struct {
        /** global ratelimit */
        u64unix_ms wait_ms;
        /** global rwlock  */
        pthread_rwlock_t rwlock;
        /** global lock */
        pthread_mutex_t lock;
    } * global;
};

/**
 * @brief Initialize ratelimiter handle
 *
 * A hashtable shall be used for storage and retrieval of discovered buckets
 * @param rl the ratelimiter handle to be initialized
 * @param conf pointer to @ref discord_rest logging module
 */
void discord_ratelimiter_init(struct discord_ratelimiter *rl,
                              struct logconf *conf);

/**
 * @brief Cleanup all buckets that have been discovered
 *
 * @note pending requests will be moved to `rest.queues->recycling`
 * @param rl the handle initialized with discord_ratelimiter_init()
 */
void discord_ratelimiter_cleanup(struct discord_ratelimiter *rl);

/**
 * @brief Iterate known buckets
 *
 * @param rl the handle initialized with discord_ratelimiter_init()
 * @param iter the user callback to be called per bucket
 */
void discord_ratelimiter_foreach_bucket(
    struct discord_ratelimiter *rl,
    void (*iter)(struct discord_ratelimiter *rl, struct discord_bucket *b));

/**
 * @brief Build unique key formed from the HTTP method and endpoint
 * @see https://discord.com/developers/docs/topics/rate-limits
 *
 * @param[in] method the request method
 * @param[out] key unique key for matching to buckets
 * @param[in] endpoint_fmt the printf-like endpoint formatting string
 * @param[in] args variadic arguments matched to `endpoint_fmt`
 */
void discord_ratelimiter_build_key(enum http_method method,
                                   char key[DISCORD_ROUTE_LEN],
                                   const char endpoint_fmt[],
                                   va_list args);

/**
 * @brief Update the bucket with response header data
 *
 * @param rl the handle initialized with discord_ratelimiter_init()
 * @param bucket NULL when bucket is first discovered
 * @param key obtained from discord_ratelimiter_build_key()
 * @param info informational struct containing details on the current transfer
 * @note If the bucket was just discovered it will be created here.
 */
void discord_ratelimiter_build(struct discord_ratelimiter *rl,
                               struct discord_bucket *bucket,
                               const char key[],
                               struct ua_info *info);

/** @brief The Discord bucket for handling per-group ratelimits */
struct discord_bucket {
    /** the hash associated with the bucket's ratelimiting group */
    char hash[64];
    /** maximum connections this bucket can handle before ratelimit */
    long limit;
    /** connections this bucket can do before waiting for cooldown */
    long remaining;
    /** timestamp of when cooldown timer resets */
    u64unix_ms reset_tstamp;
    /** pending requests */
    QUEUE(struct discord_context) pending_queue;
    /**
     * pointer to context of this bucket's currently performing request
     * @note @ref DISCORD_BUCKET_TIMEOUT if bucket is being ratelimited
     */
    struct discord_context *performing_cxt;
    /** synchronize bucket */
    pthread_mutex_t lock;
};

/**
 * @brief Return bucket timeout timestamp
 *
 * @param rl the handle initialized with discord_ratelimiter_init()
 * @param bucket the bucket to be checked for time out
 * @return the timeout timestamp
 */
u64unix_ms discord_bucket_get_timeout(struct discord_ratelimiter *rl,
                                      struct discord_bucket *bucket);

/**
 * @brief Try to timeout bucket for pending cooldown time
 *
 * @param rl the handle initialized with discord_ratelimiter_init()
 * @param bucket the bucket to wait on cooldown
 */
void discord_bucket_try_timeout(struct discord_ratelimiter *rl,
                                struct discord_bucket *b);

/**
 * @brief Get a `struct discord_bucket` assigned to `key`
 *
 * @param rl the handle initialized with discord_ratelimiter_init()
 * @param key obtained from discord_ratelimiter_build_key()
 * @return bucket matched to `key`
 */
struct discord_bucket *discord_bucket_get(struct discord_ratelimiter *rl,
                                          const char key[]);

/**
 * @brief Insert request's context into bucket's pending queue
 *
 * @param b the bucket to insert the request to
 * @param cxt the request context obtained via discord_async_start_context()
 * @param high_priority if high priority then request shall be prioritized over
 *      already enqueued requests
 */
void discord_bucket_add_context(struct discord_bucket *b,
                                struct discord_context *cxt,
                                bool high_priority);

/**
 * @brief Remove head request's context from bucket's pending queue
 *
 * @param b the bucket to fetch the request from
 * @return the request's context
 */
struct discord_context *discord_bucket_remove_context(
    struct discord_bucket *b);

/** @} DiscordInternalRESTRatelimit */

/** @brief The handle used for interfacing with Discord's REST API */
struct discord_rest {
    /** DISCORD_HTTP or DISCORD_WEBHOOK logging module */
    struct logconf conf;
    /** threadpool that manages a single REST thread */
    struct threadpool_t *tpool;
    /** the user agent handle for performing requests */
    struct user_agent *ua;
    /** store individual contexts from asynchronous requests */
    struct discord_async async;
    /** the timer queue for the rest thread */
    struct discord_timers timers;

    /** enforce ratelimiting on discovered buckets */
    struct discord_ratelimiter ratelimiter;

    /** max amount of retries before a failed request gives up */
    int retry_limit;
};

/**
 * @brief Initialize an REST handle
 *
 * Structure used for interfacing with the Discord's REST API
 * @param rest the REST handle to be initialized
 * @param conf pointer to @ref discord logging module
 * @param token the bot token
 */
void discord_rest_init(struct discord_rest *rest,
                       struct logconf *conf,
                       struct ccord_szbuf_readonly *token);

/**
 * @brief Free an REST handle
 *
 * @param rest the handle initialized with discord_rest_init()
 */
void discord_rest_cleanup(struct discord_rest *rest);

/**
 * @brief Perform a request to Discord
 *
 * This functions is a selector over discord_rest_run() or
 *        discord_rest_run_async()
 * @param rest the handle initialized with discord_rest_init()
 * @param req return object of request
 * @param body the body sent for methods that require (ex: post), leave as
 *        null if unecessary
 * @param method the method in opcode format of the request being sent
 * @param endpoint_fmt the printf-like endpoint formatting string
 * @CCORD_return
 * @note if sync is set then this function will block the thread and perform it
 *              immediately
 */
CCORDcode discord_rest_run(struct discord_rest *rest,
                           struct discord_request *req,
                           struct ccord_szbuf *body,
                           enum http_method method,
                           char endpoint_fmt[],
                           ...);

/**
 * @brief Check and manage on-going, pending and timed-out requests
 *
 * @param rest the handle initialized with discord_rest_init()
 * @CCORD_return
 */
CCORDcode discord_rest_async_perform(struct discord_rest *rest);

/**
 * @brief Stop all bucket's on-going, pending and timed-out requests
 *
 * The requests will be moved over to client's 'queues->recycling' queue
 * @param rest the handle initialized with discord_rest_init()
 */
void discord_rest_stop_buckets(struct discord_rest *rest);

/** @} DiscordInternalREST */

/** @defgroup DiscordInternalGateway WebSockets API
 * @brief Wrapper to the Discord Gateway API
 *  @{ */

/** Generic event callback */
typedef void (*discord_ev)(struct discord *client, void *event);

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

/** @brief The handle for storing the Discord response payload */
struct discord_gateway_payload {
    /** current iteration JSON string data */
    char *json;
    /** current iteration JSON string data length */
    size_t length;

    /** field 'op' */
    enum discord_gateway_opcodes opcode;
    /** field 's' */
    int seq;
    /** field 't' */
    char name[32];
    /** field 't' enumerator value */
    enum discord_gateway_events event;
    /** field 'd' */
    jsmnf_pair *data;
};

/** @brief The handle used for interfacing with Discord's Gateway API */
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
        /** timestamp of last succesful event timestamp in ms
         *      (resets every 60s) */
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

    /** parse JSON tokens into a `jsmnf_pairs` key/value pairs hashtable */
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
    struct discord_gateway_payload payload;
    /**
     * the user's callbacks for Discord events
     * @todo should be cast to the original callback signature before calling,
     *      otherwise its UB
     */
    discord_ev cbs[DISCORD_EV_MAX];
    /** the event scheduler callback */
    discord_ev_scheduler scheduler;
};

/**
 * @brief Initialize a Gateway handle
 *
 * Structure used for interfacing with the Discord's Gateway API
 * @param gw the gateway handle to be initialized
 * @param conf pointer to @ref discord logging module
 * @param token the bot token
 */
void discord_gateway_init(struct discord_gateway *gw,
                          struct logconf *conf,
                          struct ccord_szbuf_readonly *token);

/**
 * @brief Free a Gateway handle
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
 * @brief Trigger the initial handshake with the gateway
 *
 * @param gw the handle initialized with discord_gateway_init()
 * @param event provide client identification information
 */
void discord_gateway_send_identify(struct discord_gateway *gw,
                                   struct discord_identify *event);

/**
 * @brief Replay missed events when a disconnected client resumes
 *
 * @param gw the handle initialized with discord_gateway_init()
 * @param event session resume information
 */
void discord_gateway_send_resume(struct discord_gateway *gw,
                                 struct discord_resume *event);

/**
 * @brief Maintain an active gateway connection
 *
 * @param gw the handle initialized with discord_gateway_init()
 * @param seq the last session sequence number
 */
void discord_gateway_send_heartbeat(struct discord_gateway *gw, int seq);

/**
 * @brief Request all members for a guild or a list of guilds.
 *
 * @param gw the handle initialized with discord_gateway_init()
 * @param event request guild members information
 */
void discord_gateway_send_request_guild_members(
    struct discord_gateway *gw, struct discord_request_guild_members *event);

/**
 * @brief Sent when a client wants to join, move or disconnect from a voice
 *      channel
 *
 * @param gw the handle initialized with discord_gateway_init()
 * @param event request guild members information
 */
void discord_gateway_send_update_voice_state(
    struct discord_gateway *gw, struct discord_update_voice_state *event);

/**
 * @brief Send client's presence status update payload
 *
 * @param gw the handle initialized with discord_gateway_init()
 * @param event the presence to be set
 */
void discord_gateway_send_presence_update(
    struct discord_gateway *gw, struct discord_presence_update *event);

/**
 * @brief Dispatch user callback matched to event
 *
 * @param gw the handle initialized with discord_gateway_init()
 */
void discord_gateway_dispatch(struct discord_gateway *gw);

/** @} DiscordInternalGateway */

/** @defgroup DiscordInternalRefcount Reference counter
 * @brief Handle automatic cleanup of user's data
 *  @{ */

/**
 * @brief Automatically cleanup user data
 *
 * Automatically cleanup user data that is passed around Discord event's
 *      callbacks once its reference counter reaches 0, meaning there are no
 *      more callbacks expecting the data
 */
struct discord_refcounter {
    /** DISCORD_REFCOUNT logging module */
    struct logconf conf;
    /** amount of individual user's data held for automatic cleanup */
    int length;
    /** cap before increase */
    int capacity;
    /**
     * individual user's data held for automatic cleanup
     * @note datatype declared at discord-refcount.c
     */
    struct _discord_ref *refs;
};

/**
 * @brief Initialize reference counter handle
 *
 * A hashtable shall be used for storage and retrieval of user data
 * @param rc the reference counter handle to be initialized
 * @param conf pointer to @ref discord logging module
 */
void discord_refcounter_init(struct discord_refcounter *rc,
                             struct logconf *conf);

/**
 * @brief Add a new internal reference to the reference counter
 *
 * @param rc the handle initialized with discord_refcounter_init()
 * @param data the data address to be referenced
 * @param cleanup function for cleaning `data` resources once its
 *      no longer referenced
 * @param should_free whether `data` cleanup should be followed by a free()
 */
void discord_refcounter_add_internal(struct discord_refcounter *rc,
                                     void *data,
                                     void (*cleanup)(void *data),
                                     bool should_free);

/**
 * @brief Add a new client reference to the reference counter
 *
 * @param rc the handle initialized with discord_refcounter_init()
 * @param data the data address to be referenced
 * @param cleanup function for cleaning `data` resources once its
 *      no longer referenced
 * @param should_free whether `data` cleanup should be followed by a free()
 */
void discord_refcounter_add_client(struct discord_refcounter *rc,
                                   void *data,
                                   void (*cleanup)(struct discord *client,
                                                   void *data),
                                   bool should_free);

/**
 * @brief Cleanup refcounter and all user data currently held
 *
 * @param rc the handle initialized with discord_refcounter_init()
 */
void discord_refcounter_cleanup(struct discord_refcounter *rc);

/**
 * @brief Check if `data` is stored at the reference counter
 *
 * @param rc the handle initialized with discord_refcounter_init()
 * @param data the data address to be checked
 * @return `true` if data is stored
 */
bool discord_refcounter_contains(struct discord_refcounter *rc,
                                 const void *data);

/**
 * @brief Claim ownership of `data`
 * @see discord_refcounter_unclaim()
 *
 * After ownership is claimed `data` will no longer be cleaned automatically,
 *      instead shall be cleaned only when discord_refcounter_unclaim() is
 *      called
 * @param rc the handle initialized with discord_refcounter_init()
 * @param data the data to have its ownership claimed
 * @return `true` if `data` was found and claimed
 */
bool discord_refcounter_claim(struct discord_refcounter *rc, const void *data);

/**
 * @brief Unclaim ownership of `data`
 * @see discord_refcounter_claim()
 *
 * This function will have `data` cleanup method be called immediately
 * @param rc the handle initialized with discord_refcounter_init()
 * @param data the data to have its ownership unclaimed
 * @return `true` if `data` was found, unclaimed, and free'd
 */
bool discord_refcounter_unclaim(struct discord_refcounter *rc, void *data);

/**
 * @brief Increment the reference counter for `ret->data`
 * @see discord_refcounter_decr()
 *
 * @param rc the handle initialized with discord_refcounter_init()
 * @param data the data to have its reference counter incremented
 * @retval CCORD_OK counter for `data` has been incremented
 * @retval CCORD_UNAVAILABLE couldn't find a match to `data`
 * @retval CCORD_OWNERSHIP `data` has been claimed by client with
 * discord_claim()
 */
CCORDcode discord_refcounter_incr(struct discord_refcounter *rc, void *data);

/**
 * @brief Decrement the reference counter for `data`
 * @see discord_refcounter_incr()
 *
 * If the count reaches zero then `data` shall be cleanup up with its
 *      user-defined cleanup function
 * @param rc the handle initialized with discord_refcounter_init()
 * @param data the data to have its reference counter decremented
 * @retval CCORD_OK counter for `data` has been decremented
 * @retval CCORD_UNAVAILABLE couldn't find a match to `data`
 * @retval CCORD_OWNERSHIP `data` has been claimed by client with
 * discord_claim()
 */
CCORDcode discord_refcounter_decr(struct discord_refcounter *rc, void *data);

/** @} DiscordInternalRefcount */

/** @defgroup DiscordInternalMessageCommands Message Commands API
 * @brief The Message Commands API for registering and parsing user commands
 *  @{ */

/**
 * @brief The handle for storing user's message commands
 * @see discord_set_on_command()
 */
struct discord_message_commands {
    /** DISCORD_MESSAGE_COMMANDS logging module */
    struct logconf conf;
    /** the prefix expected for every command */
    struct ccord_szbuf prefix;
    /** fallback message command @see discord_set_on_command() */
    discord_ev_message fallback;
    /** amount of message commands created */
    int length;
    /** message commands cap before increase */
    int capacity;
    /**
     * message command entries
     * @note datatype declared at discord-messagecommands.c
     */
    struct _discord_message_commands_entry *entries;
};

/**
 * @brief Initialize a Message Commands handle
 *
 * @param cmds the message commands handle to be initialized
 * @param conf pointer to @ref discord logging module
 */
void discord_message_commands_init(struct discord_message_commands *cmds,
                                   struct logconf *conf);

/**
 * @brief Free a Message Commands handle
 *
 * @param cmds the handle initialized with discord_message_commands_init()
 */
void discord_message_commands_cleanup(struct discord_message_commands *cmds);

/**
 * @brief Search for a callback matching the command
 *
 * @param cmds the handle initialized with discord_message_commands_init()
 * @param command the command to be searched for
 * @param length the command length
 * @return the callback match, `NULL` in case there wasn't a match
 */
discord_ev_message discord_message_commands_find(
    struct discord_message_commands *cmds,
    const char command[],
    size_t length);

/**
 * @brief Add a new command/callback pair, or update an existing command
 *
 * @param cmds the handle initialized with discord_message_commands_init()
 * @param command the message command to be matched with callback
 * @param length the command length
 * @param callback the callback to be triggered when the command is sent
 */
void discord_message_commands_append(struct discord_message_commands *cmds,
                                     const char command[],
                                     size_t length,
                                     discord_ev_message callback);

/**
 * @brief Set a mandatory prefix before commands
 * @see discord_set_on_command()
 *
 * Example: If @a 'help' is a command and @a '!' prefix is set, the command
 *       will only be validated if @a '!help' is sent
 * @param cmds the handle initialized with discord_message_commands_init()
 * @param prefix the mandatory command prefix
 * @param length the prefix length
 */
void discord_message_commands_set_prefix(struct discord_message_commands *cmds,
                                         const char prefix[],
                                         size_t length);

/**
 * @brief Read the current @ref DISCORD_EV_MESSAGE_CREATE payload and attempt
 *      to perform its matching callback
 *
 * @param cmds the handle initialized with discord_message_commands_init()
 * @param payload the event payload to read from
 *      (assumes its from `MESSAGE_CREATE`)
 * @return `true` if the callback has been performed
 */
bool discord_message_commands_try_perform(
    struct discord_message_commands *cmds,
    struct discord_gateway_payload *payload);

/** @} DiscordInternalMessageCommands */

/**
 * @brief The Discord client handler
 *
 * Used to access/perform public functions from discord.h
 * @see discord_init(), discord_config_init(), discord_cleanup()
 */
struct discord {
    /** DISCORD logging module */
    struct logconf conf;
    /** whether this is the original client or a clone */
    bool is_original;
    /** the bot token */
    struct ccord_szbuf_readonly token;
    /** the io poller for listening to file descriptors */
    struct io_poller *io_poller;

    /** the user's message commands @see discord_set_on_command() */
    struct discord_message_commands commands;
    /** user's data reference counter for automatic cleanup */
    struct discord_refcounter refcounter;

    /** the handle for interfacing with Discord's REST API */
    struct discord_rest rest;
    /** the handle for interfacing with Discord's Gateway API */
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

    /** triggers when idle */
    discord_ev_idle on_idle;
    /** triggers once per loop cycle */
    discord_ev_idle on_cycle;

    /** space for user arbitrary data */
    void *data;

#ifdef CCORD_VOICE
    struct discord_voice vcs[DISCORD_MAX_VCS];
    struct discord_voice_evcallbacks voice_cbs;
#endif /* CCORD_VOICE */
};

/** @} DiscordInternal */

#endif /* DISCORD_INTERNAL_H */
