#ifndef LIBDISCORD_COMMON_H
#define LIBDISCORD_COMMON_H

#include <inttypes.h>
#include <pthread.h>

#include "json-scanf.h"
#include "json-actor.h"
#include "json-actor-boxed.h"

#include "user-agent.h"
#include "websockets.h"
#include "orka-utils.h"


struct discord_adapter {
  struct user_agent_s *ua;

  struct { /* RATELIMITING STRUCTURE */
    struct discord_bucket **bucket_pool; //active client buckets
    size_t num_buckets; //amount of active client buckets
    void *routes_root; //the bucket's routes encountered
    //check GNU tree functions from search.h
  } ratelimit;

  struct discord *p_client; //points to client this struct is a part of
  pthread_mutex_t lock; // used when increasing/fetching buckets
};

/* ADAPTER PRIVATE FUNCTIONS */
void discord_adapter_init(struct discord_adapter *adapter, const char token[], const char config_file[]);
void discord_adapter_cleanup(struct discord_adapter *adapter);
void discord_adapter_run(
  struct discord_adapter *adapter, 
  struct resp_handle *resp_handle,
  struct sized_buffer *req_body, // needed for POST/PUT/PATCH methods
  enum http_method http_method,
  char endpoint[],
  ...);

struct discord_bucket {
  char *hash; //the hash associated with this bucket
  int busy; //busy connections that have not yet finished its requests
  int remaining; //connections this bucket can do before cooldown
  int64_t reset_after_ms;
  u64_unix_ms_t reset_tstamp;

  u64_unix_ms_t update_tstamp; // last update timestamp
  
  // used to synchronize buckets
  pthread_mutex_t lock;
  pthread_cond_t cond;
};

/* BUCKET PRIVATE FUNCTIONS */
void discord_bucket_cleanup(struct discord_adapter *bucket);
void discord_bucket_try_cooldown(struct discord_bucket *bucket);
struct discord_bucket* discord_bucket_try_get(struct discord_adapter *adapter, char endpoint[]);
void discord_bucket_build(struct discord_adapter *adapter, struct discord_bucket *bucket, char endpoint[], struct ua_conn_s *conn);

struct cmd_cbs {
  char *str;
  message_cb *cb;
};

struct payload_s { /* PAYLOAD STRUCTURE */
  enum discord_gateway_opcodes opcode; //field 'op'
  int seq_number; //field 's'
  char event_name[64]; //field 't'
  char event_data[8192]; //field 'd'
};

struct discord_gateway { /* GATEWAY STRUCTURE */
  struct websockets_s *ws;

  struct discord_gateway_identify *identify;
  char session_id[512]; //the session id (for resuming lost connections)

  struct payload_s payload;

  struct { /* HEARTBEAT STRUCTURE */
    u64_unix_ms_t interval_ms; //fixed interval between heartbeats
    u64_unix_ms_t tstamp; //start pulse timestamp in milliseconds
  } hbeat;

  struct discord_session session;

  char *prefix; //the command prefix
  struct cmd_cbs *on_cmd; //triggers on a user set command
  size_t num_cmd; //amt of set commands

  struct { /* CALLBACKS STRUCTURE */
    idle_cb *on_idle;   //triggers in every event loop iteration
    idle_cb *on_ready; //triggers when connection first establishes
    struct { /* MESSAGE CALLBACKS STRUCTURE */
      message_cb *create; //triggers when a message is created
      sb_message_cb *sb_create; //@todo this is temporary for wrapping JS
      message_cb *update; //triggers when a message is updated (edited)
      message_delete_cb *del; //triggers when a message is deleted
      message_delete_bulk_cb *delete_bulk; //triggers when multiple messages are deleted at once
    } on_message;
    struct { /* GUILD MEMBER CALLBACKS STRUCTURE */
      guild_member_cb *add; //triggers when a member joins a guild
      guild_member_cb *update; //triggers when a member is updated
      guild_member_remove_cb *remove; //triggers when a member leaves or is removed a guild
    } on_guild_member;
    struct { /* REACTION CALLBACKS STRUCTURE */
      reaction_add_cb *add; //triggers when a reaction is added
      reaction_remove_cb *remove; //triggers when a reaction is removed
      reaction_remove_all_cb *remove_all; //triggers when all reaction are removed
      reaction_remove_emoji_cb *remove_emoji; //triggers when given emoji is removed
    } on_reaction;
  } cbs;

  int ping_ms; //latency between client and websockets server

  struct discord_user *me; //the user associated with this client
  struct sized_buffer sb_me; //@todo this is temporary for wrapping JS

  struct discord *p_client; //points to client this struct is a part of

  pthread_mutex_t lock; //for accessing gw fields within events
};

/* GATEWAY PRIVATE FUNCTIONS */
void discord_gateway_init(struct discord_gateway *gw, const char token[], const char config_file[]);
void discord_gateway_cleanup(struct discord_gateway *gw);
void discord_gateway_run(struct discord_gateway *gw);
/* gracefully exit the infinite loop */
void discord_gateway_shutdown(struct discord_gateway *gw);

struct discord {
  struct discord_adapter adapter;
  struct discord_gateway gw;
  void *data; //space for user arbitrary data
};

#endif // LIBDISCORD_COMMON_H
