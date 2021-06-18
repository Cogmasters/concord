/**
 * @file discord-internal.h
 * @author cee-studio
 * @date 18 Jun 2021
 * @brief File containing internal functions and datatypes
 */

#ifndef DISCORD_INTERNAL_H
#define DISCORD_INTERNAL_H

#include <inttypes.h>
#include <pthread.h>
#include "uthash.h"

#include "json-scanf.h"
#include "json-actor.h"
#include "json-actor-boxed.h"

#include "logconf.h" /* struct logconf */
#include "user-agent.h"
#include "websockets.h"
#include "orka-utils.h"
#include "discord-voice-connections.h"

/**
 * @brief The handle used for performing HTTP Requests 
 *
 * This is a wrapper over struct user_agent
 *        @see user-agent.h 
 */
struct discord_adapter {
  struct user_agent *ua; /**< The user agent handle for performing requests */
  struct { /* RATELIMITING STRUCTURE */
    struct discord_bucket *buckets; /**< Endpoint/routes discovered, check a endpoint/bucket match with tree search functions */
    pthread_mutex_t lock; /**< Mutex used when adding to or searching for buckets */
  } ratelimit;
  struct discord *p_client; /**< pointer to client this struct is part of */
};

/**
 * @brief Initialize the fields of a Discord Adapter handle
 *
 * @param adapter a pointer to the allocated handle
 * @param config optional pointer to a pre-initialized logconf
 * @param token the bot token
 * @see logconf.h
 */
void discord_adapter_init(struct discord_adapter *adapter, struct logconf *config, struct sized_buffer *token);

/**
 * @brief Free a Discord Adapter handle
 *
 * @param adapter a pointer to the adapter handle
 */
void discord_adapter_cleanup(struct discord_adapter *adapter);

/**
 * @brief Start a HTTP Request to Discord
 *
 * @param adapter the handle initialized with discord_adapter_init()
 * @param resp_handle the callbacks that will be triggered should the
 *        request fail or succeed
 * @param req_body the body sent for methods that require (ex: POST), 
 *        leave as #NULL if unecessary
 * @param http_method the method in opcode format of the request being sent
 *        @see user-agent.h
 * @param endpoint the format endpoint that be appended to base_url when
 *        performing a request, same behavior as printf()
 * @return a code for checking on how the transfer went
 *        #ORCA_OK means the transfer was succesful
 * @note Helper over ua_run()
 * @see user-agent.h
 * @see logconf.h
 */
ORCAcode discord_adapter_run(
  struct discord_adapter *adapter, 
  struct ua_resp_handle *resp_handle,
  struct sized_buffer *req_body,
  enum http_method http_method,
  char endpoint[], ...);

/**
 * @brief The bucket struct that will handle ratelimiting 
 *
 * @see https://discord.com/developers/docs/topics/rate-limits
 */
struct discord_bucket {
  char hash[128]; /**< the unique hash associated with this bucket */
  int busy; /**< amount of busy connections that have not yet finished its requests */
  int remaining; /**< connections this bucket can do before waiting for cooldown */
  int64_t reset_after_ms; /**< how long until cooldown timer resets */
  u64_unix_ms_t reset_tstamp; /**< timestamp of when cooldown timer resets */
  
  u64_unix_ms_t update_tstamp; /**< timestamp of the most recent request */
  
  pthread_mutex_t lock; /**< synchronize buckets between threads */
  pthread_cond_t cond;
  
  char route[256]; /**< this bucket 'key' */
  UT_hash_handle hh; /**< makes this structure hashable */
};

/**
 * @brief Free client buckets
 *
 * @param adapter the client adapter containinig every bucket found
 */
void discord_buckets_cleanup(struct discord_adapter *adapter);

/**
 * @brief Check bucket for ratelimit cooldown
 *
 * Check if connections from a bucket hit its threshold, and lock every connection
 *        associated with the bucket until cooldown time elapses
 *  @param bucket check if a cooldown is necessary
 */
void discord_bucket_try_cooldown(struct discord_bucket *bucket);

/**
 *  @brief Get existing bucket with @p route
 *
 *  Check if bucket associated with @p route has already been discovered
 *  @param adapter the handle created with discord_adapter_init()
 *  @param bucket check if a cooldown is necessary
 *  @param route that will be checked for a bucket match
 *  @return bucket associated with route or #NULL if no match found
 */
struct discord_bucket* discord_bucket_try_get(struct discord_adapter *adapter, const char route[]);

/**
 * @brief Update the bucket with response header data
 *
 * @param adapter the handle created with discord_adapter_init()
 * @param bucket #NULL when bucket is first discovered
 * @param route the route associated with the bucket
 * @param info information struct regarding the current transfer
 * @note If the bucket was just discovered it will be created here.
 */
void discord_bucket_build(struct discord_adapter *adapter, struct discord_bucket *bucket, const char route[], struct ua_info *info);

/**
 * @brief The handle used for establishing a Discord Gateway connection
 *        via WebSockets
 *
 * @note A wrapper over struct websockets
 * @see websockets.h 
 */
struct discord_gateway {
  struct websockets *ws; /**< the websockets handle that connects to Discord */
  struct { /* RECONNECT STRUCTURE */
    bool enable; /**< will attempt reconnecting if true */
    int attempt; /**< current reconnect attempt (resets to 0 when succesful) */
    int threshold; /**< max amount of reconnects before giving up */
  } reconnect;
  bool is_resumable; /**< will attempt to resume session if connection shutsdowns */
  bool is_ready; /**< can start sending/receiving additional events to discord */
  bool shutdown; /**< if #true shutdown websockets connection as soon as possible */

  struct discord_gateway_identify *id; /**< this info sent expecting a connection authentication */
  char session_id[512]; /**< the session id (for resuming lost connections) */
  
 // https://discord.com/developers/docs/topics/gateway#payloads-gateway-payload-structure
  struct { /* GATEWAY PAYLOAD STRUCTURE */
    enum discord_gateway_opcodes opcode; /**< field 'op' */
    int seq_number;                      /**< field 's' */
    char event_name[64];                 /**< field 't' */
    struct sized_buffer event_data;      /**< field 'd' */
  } payload;

  // Discord expects a proccess called heartbeating in order to keep the client-server connection alive
  // https://discord.com/developers/docs/topics/gateway#heartbeating
  struct { /* HEARTBEAT STRUCTURE */
    u64_unix_ms_t interval_ms; /**< fixed interval between heartbeats */
    u64_unix_ms_t tstamp; /**< start pulse timestamp in milliseconds */
  } hbeat;

  struct discord_session session; /**< on-going Discord Gateway session */

  struct sized_buffer prefix; /**< the prefix expected before every command @see discord_set_prefix() */
  struct { /**< user's command/callback pair and amount of callback pairs @see discord_set_on_command() */
    char *start,
    size_t size;
    message_cb *cb;
  } on_default_cmd, *on_cmd;
  size_t num_cmd; 

  struct { /* CALLBACKS STRUCTURE */
    idle_cb *on_idle; /**< triggers on every event loop iteration */
    event_raw_cb *on_event_raw; /**< triggers for every event if set, receive its raw JSON string */
    idle_cb *on_ready; /**< triggers when connection first establishes */
    guild_role_cb *on_guild_role_create; /**< triggers when a guild role is created */
    guild_role_cb *on_guild_role_update; /**< triggers when a guild role is updated */
    guild_role_delete_cb *on_guild_role_delete; /**< triggers when a guild role is deleted */
    guild_member_cb *on_guild_member_add; /**< triggers when a guild member joins a guild */
    guild_member_remove_cb *on_guild_member_remove; /**< triggers when a guild member is removed from a guild */
    guild_member_cb *on_guild_member_update; /**< triggers when a guild member status is updated (ex: receive role) */
    guild_ban_cb *on_guild_ban_add; /**< triggers when a ban occurs */
    guild_ban_cb *on_guild_ban_remove; /**< triggers when a ban is removed */
    channel_cb *on_channel_create; /**< triggers when a channel is created */
    channel_cb *on_channel_update; /**< triggers when a channel is updated */
    channel_cb *on_channel_delete; /**< triggers when a channel is deleted */
    channel_pins_update_cb *on_channel_pins_update; /**< triggers when a channel pinned messages updates */
    message_cb *on_message_create; /**< triggers when a message is created */
    sb_message_cb *sb_on_message_create; /**< @todo this is temporary */
    message_cb *on_message_update; /**< trigger when a message is updated */
    sb_message_cb *sb_on_message_update; /**< @todo this is temporary */
    message_delete_cb *on_message_delete; /**< triggers when a message is deleted */
    message_delete_bulk_cb *on_message_delete_bulk; /**< triggers when a bulk of messages is deleted */
    message_reaction_add_cb *on_message_reaction_add; /**< triggers when a reaction is added to a message */
    message_reaction_remove_cb *on_message_reaction_remove; /**< triggers when a reaction is removed from a message */
    message_reaction_remove_all_cb *on_message_reaction_remove_all; /**< triggers when all reactions are removed from a message */
    message_reaction_remove_emoji_cb *on_message_reaction_remove_emoji; /**< triggers when all occurences of a specific reaction is removed from a message */
    voice_state_update_cb *on_voice_state_update; /**< triggers when a voice state is updated */
    voice_server_update_cb *on_voice_server_update; /**< triggers when a voice server is updated */
  } cbs;

  enum discord_event_handling_mode (*blocking_event_handler)(void *cxt);
  
  int ping_ms; /**< latency between client and websockets server, calculated by the interval between HEARTBEAT and HEARTBEAT_ACK */

  pthread_mutex_t lock;
  
  struct discord_user *bot; /**< the bot user structure */
  struct sized_buffer sb_bot; /**< @todo this is temporary */

  struct discord *p_client; /**< pointer to client this struct is part of */
};

/**
 * Wbrief Initialize the fields of Discord Gateway handle
 *
 * @param gw a pointer to the allocated handle
 * @param config optional pointer to a initialized logconf
 * @param the bot token
 * @see logconf.h
 */
void discord_gateway_init(struct discord_gateway *gw, struct logconf *config, struct sized_buffer *token);

/**
 * @brief Free a Discord Gateway handle
 *
 * @param gw a pointer to the gateway handle
 */
void discord_gateway_cleanup(struct discord_gateway *gw);

/**
 * @brief Start a Discord connection over WebSockets
 *
 * @param gw the handle initialized with discord_gateway_init()
 * @see websockets.h
 */
void discord_gateway_run(struct discord_gateway *gw);

/**
 * @brief Gracefully exits a ongoing Discord connection over WebSockets
 *
 * @param gw the handle initialized with discord_gateway_init()
 * @see websockets.h
 */
void discord_gateway_shutdown(struct discord_gateway *gw);

/**
 * @brief Gracefully reconnect a ongoing Discord connection over WebSockets
 *
 * @param gw the handle initialized with discord_gateway_init()
 * @param resume #TRUE to attempt to resume to previous session,
 *        #FALSE restart a fresh session
 * @see websockets.h
 */
void discord_gateway_reconnect(struct discord_gateway *gw, bool resume);


/**
 * @brief The Discord Client structure
 *
 * Used to access/perform public functions from discord.h 
 */
struct discord {
  struct sized_buffer token; /**< the bot token */
  struct discord_adapter adapter; /**< the HTTP adapter for performing requests */
  struct discord_gateway gw; /**< the WebSockets handle for establishing a connection to Discord */
  
  struct logconf config; /**< store bot.config file contents and sync logging between adapter/gw */

#define NUM_VCS 512
  struct discord_voice vcs[NUM_VCS];
  struct discord_voice_cbs voice_cbs;

  void *data; /**< space for user arbitrary data @see discord_get_data() and discord_set_data() */
};

struct discord_event_cxt {
  char event_name[64];
  pthread_t tid; /**< the thread id */
  struct sized_buffer data; /**< a copy of payload data */
  struct discord_gateway *p_gw; /**< the gateway client */
  enum discord_gateway_events event;
  void (*on_event)(
    struct discord_gateway *gw,
    struct sized_buffer *data);
  bool is_main_thread;
};

#endif // DISCORD_INTERNAL_H
