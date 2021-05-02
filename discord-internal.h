#ifndef DISCORD_INTERNAL_H
#define DISCORD_INTERNAL_H

#include <inttypes.h>
#include <pthread.h>

#include "json-scanf.h"
#include "json-actor.h"
#include "json-actor-boxed.h"

#include "logconf.h" /* struct logconf */
#include "user-agent.h"
#include "websockets.h"
#include "orka-utils.h"

/**
 * The handle used for performing HTTP Requests 
 *
 * @note A wrapper over struct user_agent
 *        @see user-agent.h 
 */
struct discord_adapter {
  // the user agent handle that performs requests
  struct user_agent *ua;

  struct { /* RATELIMITING STRUCTURE */
    // buckets discovered and its amount
    struct discord_bucket **bucket_pool;
    size_t num_buckets;
    // endpoint/routes discovered, check a endpoint/bucket matchwith tree search functions
    void *routes_root; /** @see search.h root */

    // lock when adding/searching for buckets
    pthread_mutex_t lock;
  } ratelimit;
  
  // pointer to client this struct is part of
  struct discord *p_client;
};

/**
 * Initialize the fields of a Discord Adapter handle
 *
 * @param adapter a pointer to the pre-allocated handle
 * @param config optional pointer to a pre-initialized logconf
 *        @note normally it is the struct discord logconf
 *        @see logconf.h for definition
 * @param token the bot token
 */
void discord_adapter_init(struct discord_adapter *adapter, struct logconf *config, struct sized_buffer *token);

/**
 * Free a Discord Adapter handle
 */
void discord_adapter_cleanup(struct discord_adapter *adapter);

/**
 * Start a HTTP Request to Discord
 *
 * @note Helper over ua_run()
 *    @see user-agent.h
 *
 * @param adapter the handle created with discord_adapter_init()
 * @param resp_handle the callbacks that will be triggered should the
 *        request fail or succeed
 * @param req_body the body sent for methods that require them (ex: POST), leave as #NULL if unecessary
 * @param http_method the method in opcode format of the request being sent
 *        @see user-agent.h
 * @param endpoint the format endpoint that be appended to base_url when
 *        performing a request, same behavior as printf()
 */
void discord_adapter_run(
  struct discord_adapter *adapter, 
  struct ua_resp_handle *resp_handle,
  struct sized_buffer *req_body, // needed for POST/PUT/PATCH methods
  enum http_method http_method,
  char endpoint[], ...);

/* The bucket struct that will handle ratelimiting */
struct discord_bucket {
  // the unique hash associated with this bucket
  char *hash;
  // amount of busy connections that have not yet finished its requests
  int busy;
  // connections this bucket can do before waiting for cooldown
  int remaining;
  // how long until cooldown timer resets
  int64_t reset_after_ms;
  // timestamp of when cooldown timer resets
  u64_unix_ms_t reset_tstamp;
  
  // timestamp of the most recent request
  u64_unix_ms_t update_tstamp;
  
  // synchronize buckets between threads
  pthread_mutex_t lock;
  pthread_cond_t cond;
};

/**
 * Free a bucket
 */
void discord_bucket_cleanup(struct discord_adapter *bucket);

/**
 * Check if connections from a bucket hit its threshold, and lock every connection
 *        associated with the bucket until cooldown time elapses
 *
 *  @param bucket check if a cooldown is necessary
 */
void discord_bucket_try_cooldown(struct discord_bucket *bucket);

/**
 *  Check if bucket associated with given endpoint has already been discovered
 *
 *  @param adapter the handle created with discord_adapter_init()
 *  @param bucket check if a cooldown is necessary
 *  @return bucket associated with endpoint or #NULL if no match found
 */
struct discord_bucket* discord_bucket_try_get(struct discord_adapter *adapter, char endpoint[]);

/**
 * Update the bucket internal information from the response header
 * @note if the bucket was just discovered, it will be created here
 *
 * @param adapter the handle created with discord_adapter_init()
 * @param bucket #NULL when bucket is first discovered
 * @param endpoint the endpoint associated with the bucket
 * @conn the connection node that performed the request
 */
void discord_bucket_build(struct discord_adapter *adapter, struct discord_bucket *bucket, char endpoint[], struct ua_conn *conn);

/** 
 * Struct for storing user-specific commands/callback pair for the bot to listen 
 *        and execute
 * @see discord_set_on_command()
 */
struct cmd_cbs {
  char *str;
  message_cb *cb;
};

/**
 * The handle used for establishing a Discord Gateway connection
 *        via WebSockets
 *
 * @note A wrapper over struct websockets
 *        @see websockets.h 
 */
struct discord_gateway {
  // the websockets handle that connects to Discord
  struct websockets *ws;
  // handle reconnect logic
  struct { /* RECONNECT STRUCTURE */
    // will attempt reconnecting if true
    bool enable;
    // current reconnect attempt (resets to 0 when succesful)
    int attempt;
    // max amount of reconnects before giving up
    int threshold;
  } reconnect;
  // will attempt to resume session if connection shutsdowns
  bool is_resumable; 
  // can start sending/receiving additional events to discord
  bool is_ready; 

  bool shutdown;

  // this info sent expecting a connection authentication
  struct discord_gateway_identify *id; /** @see specs/gateway.json and specs-code/gateway.h for definition */
  // the session id (for resuming lost connections)
  char session_id[512]; 
  
  /// @see https://discord.com/developers/docs/topics/gateway#payloads-gateway-payload-structure
  struct { /* GATEWAY PAYLOAD STRUCTURE */
    enum discord_gateway_opcodes opcode; // field 'op'
    int seq_number;                      // field 's'
    char event_name[64];                 // field 't'
    struct sized_buffer event_data;      // field 'd'
  } payload;

  /// @note Discord expects a proccess called heartbeating in order to keep the client-server connection alive
  /// @see https://discord.com/developers/docs/topics/gateway#heartbeating
  struct { /* HEARTBEAT STRUCTURE */
    // fixed interval between heartbeats
    u64_unix_ms_t interval_ms;
    // start pulse timestamp in milliseconds
    u64_unix_ms_t tstamp;
  } hbeat;

  // on-going Discord Gateway session
  struct discord_session session; /** @see discord.h for definition */

  // the prefix expected before every command
  char prefix[32]; /** @see discord_set_prefix() */
  // user's command/callback pair and amount of callback pairs
  struct cmd_cbs *on_cmd; /** @see discord_set_on_command() */
  size_t num_cmd;

  /// @see discord.h for definition
  struct { /* CALLBACKS STRUCTURE */
    // triggers on every event loop iteration
    idle_cb *on_idle; /** @see discord_set_on_idle() */
    
    // triggers for every event if set
    /// @note will include the event payload in its raw string format
    event_raw_cb *on_event_raw; /** @see discord_set_on_event_raw() */

    /// @see discord_set_on_xxx() for every matching callback function
    // triggers when connection first establishes
    idle_cb *on_ready;
    // triggers when a guild role is created
    guild_role_cb *on_guild_role_create;
    // triggers when a guild role is updated
    guild_role_cb *on_guild_role_update;
    // triggers when a guild role is deleted
    guild_role_delete_cb *on_guild_role_delete;
    // triggers when a guild member joins a guild
    guild_member_cb *on_guild_member_add;
    // triggers when a guild member is removed from a guild
    guild_member_remove_cb *on_guild_member_remove;
    // triggers when a guild member status is updated (ex: receive role)
    guild_member_cb *on_guild_member_update;
    // triggers when a ban occurs
    guild_ban_cb *on_guild_ban_add;
    // triggers when a ban is removed
    guild_ban_cb *on_guild_ban_remove;
    // triggers when a channel is created
    channel_cb *on_channel_create;
    // triggers when a channel is updated
    channel_cb *on_channel_update;
    // triggers when a channel is deleted
    channel_cb *on_channel_delete;
    // triggers when a channel pinned messages updates
    channel_pins_update_cb *on_channel_pins_update;
    // triggers when a message is created
    message_cb *on_message_create;
    sb_message_cb *sb_on_message_create; /** @todo this is temporary */
    // trigger when a message is updated
    message_cb *on_message_update;
    sb_message_cb *sb_on_message_update; /** @todo this is temporary */
    // triggers when a message is deleted
    message_delete_cb *on_message_delete;
    // triggers when a bulk of messages is deleted
    message_delete_bulk_cb *on_message_delete_bulk;
    // triggers when a reaction is added to a message
    message_reaction_add_cb *on_message_reaction_add;
    // triggers when a reaction is removed from a message
    message_reaction_remove_cb *on_message_reaction_remove;
    // triggers when all reactions are removed from a message
    message_reaction_remove_all_cb *on_message_reaction_remove_all;
    // triggers when all occurences of a specific reaction is removed from a message
    message_reaction_remove_emoji_cb *on_message_reaction_remove_emoji;
    // triggers when a voice state is updated
    voice_state_update_cb *on_voice_state_update;
    // triggers when a voice server is updated
    voice_server_update_cb *on_voice_server_update;
  } cbs;

  // The function will handle an event in the current thread and return
  // true, otherwise it return false and the event will be passed to
  // a newly created thread.
  enum discord_event_handling_mode (*blocking_event_handler)(void *cxt);
  
  // latency between client and websockets server
  /// @note calculated by interval response between HEARTBEAT and HEARTBEAT_ACK
  int ping_ms; /** @todo implement discord_gateway_ping_ms() */

  pthread_mutex_t lock;
  
  // the bot user structure
  struct discord_user *bot;
  struct sized_buffer sb_bot; /** @todo this is temporary */

  // pointer to client this struct is part of
  struct discord *p_client;
};

/**
 * Initialize the fields of Discord Gateway handle
 *
 * @param gw a pointer to the pre-allocated handle
 * @param config optional pointer to a pre-initialized logconf
 *        @note normally it is the struct discord logconf
 *        @see logconf.h for definition
 * @param the bot token
 */
void discord_gateway_init(struct discord_gateway *gw, struct logconf *config, struct sized_buffer *token);

/**
 * Free a Discord Gateway handle
 */
void discord_gateway_cleanup(struct discord_gateway *gw);

/**
 * Start a Discord connection over WebSockets
 *
 * @note Wraps around ws_perform() / ws_wait_activity()
 *        @see websockets.h
 *
 * @param gw the handle initialized with discord_gateway_init()
 */
void discord_gateway_run(struct discord_gateway *gw);

/**
 * Gracefully exits a ongoing Discord connection over WebSockets
 * @note Wraps around ws_set_action()
 *        @see websockets.h
 * 
 * @param gw the handle initialized with discord_gateway_init()
 */
void discord_gateway_shutdown(struct discord_gateway *gw);

/**
 * Gracefully reconnect a ongoing Discord connection over WebSockets
 * @note Wraps around ws_set_action()
 *        @see websockets.h
 * 
 * @param gw the handle initialized with discord_gateway_init()
 * @param resume #TRUE to attempt to resume to previous session,
 *        #FALSE restart a fresh session
 */
void discord_gateway_reconnect(struct discord_gateway *gw, bool resume);


/* The Discord Client structure, used to performing every kind of
 *  function from discord.h */
struct discord {
  // the bot token
  struct sized_buffer token;
  // the HTTP adapter for performing requests
  struct discord_adapter adapter;
  // the WebSockets handle for establishing a connection to Discord
  struct discord_gateway gw;
  
  // store bot.config file contents and sync logging between adapter/gw
  struct logconf config;

#ifdef DISCORD_VOICE_CONNECTIONS_H
#define NUM_VCS 512
  struct discord_voice vcs[NUM_VCS];
#endif // DISCORD_VOICE_CONNECTIONS_H
  
  // space for user arbitrary data
  /// @see discord_get_data() and discord_set_data()
  void *data;
};

struct discord_event_cxt {
  char event_name[64];
  pthread_t tid; // the thread id
  struct sized_buffer data; // a copy of payload data
  struct discord_gateway *p_gw; // the gateway client
  enum discord_gateway_events event;
  void (*on_event)(
    struct discord_gateway *gw,
    struct sized_buffer *data);
  bool is_main_thread;
};

#endif // DISCORD_INTERNAL_H
