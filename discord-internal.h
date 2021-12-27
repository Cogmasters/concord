/**
 * @file discord-internal.h
 * @author cee-studio
 * @brief File containing internal functions and datatypes
 */

#ifndef DISCORD_INTERNAL_H
#define DISCORD_INTERNAL_H

#include <inttypes.h>
#include <pthread.h>

#include "json-actor.h"

#include "logconf.h" /* struct logconf */
#include "user-agent.h"
#include "websockets.h"
#include "work.h"
#include "cee-utils.h"

#include "uthash.h"
#include "queue.h"
#include "heap-inl.h"

#include "discord-voice-connections.h"

/** @brief Get client from its nested field */
#define CLIENT(ptr, path) CONTAINEROF(ptr, struct discord, path)

/** @brief Behavior of request return object */
struct discord_request_attr {
  /** the object itself */
  void *obj;
  /** size of `obj` in bytes */
  size_t size;
  /** initialize `obj` fields */
  void (*init)(void *obj);
  /** callback for filling `obj` with JSON values */
  void (*from_json)(char *json, size_t len, void *obj);
  /** perform a cleanup on `obj` */
  void (*cleanup)(void *obj);

  /** in case of HTTP_MIMEPOST, provide attachments */
  struct discord_attachment **attachments;
};

#define DISCORD_ENDPT_LEN 2048
#define DISCORD_ROUTE_LEN 256

/**
 * @brief Context of individual requests that are scheduled to run
 *        asynchronously
 */
struct discord_context {
  /** async return object attributes */
  struct discord_request_attr attr;
  /** the request's bucket */
  struct discord_bucket *bucket;
  /** callback to be executed on request completion */
  discord_on_done done;
  /** callback to be executed on request failure */
  discord_on_fail fail;

  /** the request's body @note buffer is kept and recycled */
  struct {
    struct sized_buffer buf;
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
  /** the min-heap node (for selecting timeouts) */
  struct heap_node node;
  /** the timeout timestamp */
  u64_unix_ms_t timeout_ms;

  /** user arbitrary data */
  struct {
    void *data;
    void (*cleanup)(void *data);
  } udata;

  /** current retry attempt (stop at adapter->retry_limit) */
  int retry_attempt;
};

/** @brief The handle used for performing HTTP Requests */
struct discord_adapter {
  /** DISCORD_HTTP or DISCORD_WEBHOOK logging module */
  struct logconf conf;
  /** the user agent handle for performing requests */
  struct user_agent *ua;
  /** if true next request will be dealt with asynchronously */
  bool async_enable;
  /** curl_multi handle for performing non-blocking requests */
  CURLM *mhandle;
  /** routes discovered (declared at discord-adapter-ratelimit.c) */
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
    u64_unix_ms_t wait_ms;
    /** global rwlock  */
    pthread_rwlock_t rwlock;
    /** global lock */
    pthread_mutex_t lock;
  } * global;

  /** async requests handling */
  struct {
    /** attributes for next async request */
    struct discord_async_attr attr;
    /** reusable buffer for async return objects */
    struct sized_buffer obj;
    /** idle request handles of type 'struct discord_context' */
    QUEUE *idleq;
    /* request timeouts */
    struct heap timeouts;
  } async;

  /** error storage */
  char errbuf[2048];
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
 * @param adapter a pointer to the adapter handle
 */
void discord_adapter_cleanup(struct discord_adapter *adapter);

/**
 * @brief Perform a request to Discord
 *
 * This functions is a selector over discord_adapter_run() or
 *        discord_adapter_run_async()
 * @param adapter the handle initialized with discord_adapter_init()
 * @param attr attributes of request
 * @param body the body sent for methods that require (ex: post), leave as
 *        null if unecessary
 * @param method the method in opcode format of the request being sent
 * @param endpoint_fmt the printf-like endpoint formatting string
 * @ORCA_return
 * @note if async is set then this function will enqueue the request instead of
 * performing it immediately
 */
ORCAcode discord_adapter_run(struct discord_adapter *adapter,
                             struct discord_request_attr *attr,
                             struct sized_buffer *body,
                             enum http_method method,
                             char endpoint_fmt[],
                             ...);

/**
 * @brief Set next request to run asynchronously
 *
 * @param adapter the handle initialized with discord_adapter_init()
 * @param attr async attributes for next request
 */
void discord_adapter_async_next(struct discord_adapter *adapter,
                                struct discord_async_attr *attr);

/**
 * @brief Check and manage on-going, pending and timed-out requests
 *
 * @param adapter the handle initialized with discord_adapter_init()
 * @ORCA_return
 */
ORCAcode discord_adapter_perform(struct discord_adapter *adapter);

/**
 * @brief Get global timeout timestamp
 *
 * @param adapter the handle initialized with discord_adapter_init()
 * @return the most recent global timeout timestamp
 */
u64_unix_ms_t discord_adapter_get_global_wait(struct discord_adapter *adapter);

/**
 * @brief Stop all on-going, pending and timed-out requests
 *
 * The requests will be moved over to client's 'idleq' queue
 * @param adapter the handle initialized with discord_adapter_init()
 */
void discord_adapter_stop_all(struct discord_adapter *adapter);

/** @brief The bucket struct for handling ratelimiting */
struct discord_bucket {
  /** the hash associated with this bucket */
  char hash[64];
  /** maximum connections this bucket can handle before ratelimit */
  long limit;
  /** connections this bucket can do before waiting for cooldown */
  long remaining;
  /** timestamp of when cooldown timer resets */
  u64_unix_ms_t reset_tstamp;
  /** synchronize ratelimiting between threads */
  pthread_mutex_t lock;
  /** pending requests of type 'struct discord_context' */
  QUEUE waitq;
  /** busy requests of type 'struct discord_context' */
  QUEUE busyq;
  /** avoid excessive timeouts */
  bool freeze;
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
u64_unix_ms_t discord_bucket_get_timeout(struct discord_adapter *adapter,
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

struct discord_gateway_cmd_cbs {
  char *start;
  size_t size;
  discord_on_message cb;
};

struct discord_gateway_cbs {
  /** triggers on every event loop iteration */
  discord_on_idle on_idle;

  /** triggers when connection first establishes */
  discord_on_idle on_ready;

  /** triggers when a command is created */
  discord_on_application_command on_application_command_create;
  /** triggers when a command is updated */
  discord_on_application_command on_application_command_update;
  /** triggers when a command is deleted */
  discord_on_application_command on_application_command_delete;

  /** triggers when a channel is created */
  discord_on_channel on_channel_create;
  /** triggers when a channel is updated */
  discord_on_channel on_channel_update;
  /** triggers when a channel is deleted */
  discord_on_channel on_channel_delete;
  /** triggers when a channel pinned messages updates */
  discord_on_channel_pins_update on_channel_pins_update;
  /** triggers when a thread is created */
  discord_on_channel on_thread_create;
  /** triggers when a thread is updated */
  discord_on_channel on_thread_update;
  /** triggers when a thread is deleted */
  discord_on_channel on_thread_delete;

  /** triggers when guild info is ready, or a guild has joined */
  discord_on_guild on_guild_create;
  /** triggers when a guild's information is updated */
  discord_on_guild on_guild_update;
  /** triggers when removed from guild */
  discord_on_guild_delete on_guild_delete;

  /** triggers when a ban occurs */
  discord_on_guild_ban on_guild_ban_add;
  /** triggers when a ban is removed */
  discord_on_guild_ban on_guild_ban_remove;

  /** triggers when a guild member joins a guild */
  discord_on_guild_member on_guild_member_add;
  /** triggers when a guild member is removed from a guild */
  discord_on_guild_member_remove on_guild_member_remove;
  /** triggers when a guild member status is updated (ex: receive role) */
  discord_on_guild_member on_guild_member_update;

  /** triggers when a guild role is created */
  discord_on_guild_role on_guild_role_create;
  /** triggers when a guild role is updated */
  discord_on_guild_role on_guild_role_update;
  /** triggers when a guild role is deleted */
  discord_on_guild_role_delete on_guild_role_delete;

  /** triggers when a interaction is created  */
  discord_on_interaction on_interaction_create;

  /** triggers when a message is created */
  discord_on_message on_message_create;
  /** trigger when a message is updated */
  discord_on_message on_message_update;
  /** triggers when a message is deleted */
  discord_on_message_delete on_message_delete;
  /** triggers when a bulk of messages is deleted */
  discord_on_message_delete_bulk on_message_delete_bulk;
  /** triggers when a reaction is added to a message */
  discord_on_message_reaction_add on_message_reaction_add;
  /** triggers when a reaction is removed from a message */
  discord_on_message_reaction_remove on_message_reaction_remove;
  /** triggers when all reactions are removed from a message */
  discord_on_message_reaction_remove_all on_message_reaction_remove_all;
  /** triggers when all occurences of a specific reaction is removed from a
   * message */
  discord_on_message_reaction_remove_emoji on_message_reaction_remove_emoji;

  /** triggers when a voice state is updated */
  discord_on_voice_state_update on_voice_state_update;
  /** triggers when a voice server is updated */
  discord_on_voice_server_update on_voice_server_update;
};

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
    u64_unix_ms_t interval;
    /** last heartbeat pulse timestamp */
    u64_unix_ms_t hbeat;
    /** Gateway's concept of "now" */
    u64_unix_ms_t now;
    /** timestamp of last succesful identify request */
    u64_unix_ms_t identify;
    /** timestamp of last succesful event timestamp in ms (resets every 60s) */
    u64_unix_ms_t event;
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
    char id[512];
    /** amount of shards being used by this session */
    int shards;
    /** session limits */
    struct discord_session_start_limit start_limit;
    /** active concurrent sessions */
    int concurrent;
    /** event counter to avoid reaching limit of 120 events per 60 sec */
    int event_count;

    /** session status */
    enum {
      /** client is currently offline */
      DISCORD_SESSION_OFFLINE = 0,
      /** client will attempt to resume session after reconnect */
      DISCORD_SESSION_RESUMABLE = 1 << 0,
      /** client in the process of being shutdown */
      DISCORD_SESSION_SHUTDOWN = 1 << 1
    } status;

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

  /** response-payload structure */
  struct {
    /** field 'op' */
    enum discord_gateway_opcodes opcode;
    /** field 's' */
    int seq;
    /** field 't' */
    char name[64];
    /** field 'd' */
    struct sized_buffer data;
  } payload;

  /** user-commands structure */
  struct {
    /** the prefix expected for every command */
    struct sized_buffer prefix;
    /** user's command/callback pair @see discord_set_on_command() */
    struct discord_gateway_cmd_cbs *pool;
    /** amount of command/callback pairs in pool */
    size_t amt;
    /** fallback function incase prefix matches but command doesn't */
    struct discord_gateway_cmd_cbs on_default;
    /** user's callbacks */
    struct discord_gateway_cbs cbs;
    /** event execution flow callback */
    discord_on_scheduler scheduler;
  } cmds;
};

/**
 * @brief Context in case event is scheduled to be triggered
 *        from Orca's worker threads
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
  void (*on_event)(struct discord_gateway *gw, struct sized_buffer *data);
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
 * @ORCA_return
 */
ORCAcode discord_gateway_start(struct discord_gateway *gw);

/**
 * @brief Cleanup and reset `gw` session primitives
 *
 * @param ws the WebSockets handle created with ws_init()
 * @return `true` if session can be retried, `false` otherwise
 */
bool discord_gateway_end(struct discord_gateway *gw);

/**
 * @brief Check and manage on-going Gateway session
 *
 * @param req the request handler
 * @ORCA_return
 */
ORCAcode discord_gateway_perform(struct discord_gateway *gw);

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
 * @brief The Discord client handler
 *
 * Used to access/perform public functions from discord.h
 * @see discord_init(), discord_config_init(), discord_cleanup()
 */
struct discord {
  /** @privatesection */
  /** DISCORD logging module */
  struct logconf conf;
  /** whether this is the original client or a clone */
  bool is_original;
  /** the bot token */
  struct sized_buffer token;
  /** the HTTP adapter for performing requests */
  struct discord_adapter adapter;
  /** the WebSockets handle for establishing a connection to Discord */
  struct discord_gateway gw;
  /** the WebSockets handles for establishing voice connections to Discord */
  struct discord_voice vcs[DISCORD_MAX_VOICE_CONNECTIONS];
  /** @todo create a analogous struct for Gateway's callbacks */
  struct discord_voice_cbs voice_cbs;
  /** the client's user structure */
  struct discord_user self;
  /** space for user arbitrary data */
  void *data;
};

#endif /* DISCORD_INTERNAL_H */
