#ifndef DISCORD_COMMON_H
#define DISCORD_COMMON_H

#include <inttypes.h>
#include <pthread.h>

#include "json-scanf.h"
#include "json-actor.h"
#include "json-actor-boxed.h"

#include "user-agent.h"
#include "websockets.h"
#include "orka-utils.h"


struct discord_adapter {
  struct user_agent *ua;

  struct { /* RATELIMITING STRUCTURE */
    struct discord_bucket **bucket_pool; //active client buckets
    size_t num_buckets; //amount of active client buckets
    void *routes_root; //the bucket's routes encountered (see search.h)
    pthread_mutex_t lock; // used when increasing/fetching buckets
  } ratelimit;

  struct discord *p_client; //points to client this struct is a part of
};

/* ADAPTER PRIVATE FUNCTIONS */
void discord_adapter_init(struct discord_adapter *adapter, const char token[]);
void discord_adapter_config_init(struct discord_adapter *adapter, const char config_file[]);
void discord_adapter_cleanup(struct discord_adapter *adapter);
void discord_adapter_run(
  struct discord_adapter *adapter, 
  struct ua_resp_handle *resp_handle,
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
void discord_bucket_build(struct discord_adapter *adapter, struct discord_bucket *bucket, char endpoint[], struct ua_conn *conn);

struct cmd_cbs {
  char *str;
  message_cb *cb;
};

struct discord_gateway_payload { /* GATEWAY PAYLOAD STRUCTURE */
  enum discord_gateway_opcodes opcode; //field 'op'
  int seq_number;                      //field 's'
  char event_name[64];                 //field 't'
  struct sized_buffer event_data;      //field 'd'
};

struct discord_gateway { /* GATEWAY STRUCTURE */
  struct websockets *ws;

  struct discord_gateway_identify *id;
  char session_id[512]; //the session id (for resuming lost connections)

  struct discord_gateway_payload payload;

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
    idle_cb *on_ready;  //triggers when connection first establishes

    event_raw_cb *on_event_raw;

    guild_role_cb *on_guild_role_create;
    guild_role_cb *on_guild_role_update;
    guild_role_delete_cb *on_guild_role_delete;
    guild_member_cb *on_guild_member_add;
    guild_member_remove_cb *on_guild_member_remove;
    guild_member_cb *on_guild_member_update;
    guild_ban_cb *on_guild_ban_add;
    guild_ban_cb *on_guild_ban_remove;
    channel_cb *on_channel_create;
    channel_cb *on_channel_update;
    channel_cb *on_channel_delete;
    channel_pins_update_cb *on_channel_pins_update;
    message_cb *on_message_create;
    sb_message_cb *sb_on_message_create; //@todo this is temporary
    sb_message_cb *sb_on_message_update; //@todo this is temporary
    message_cb *on_message_update;
    message_delete_cb *on_message_delete;
    message_delete_bulk_cb *on_message_delete_bulk;
    message_reaction_add_cb *on_message_reaction_add;
    message_reaction_remove_cb *on_message_reaction_remove;
    message_reaction_remove_all_cb *on_message_reaction_remove_all;
    message_reaction_remove_emoji_cb *on_message_reaction_remove_emoji;
    voice_state_update_cb *on_voice_state_update;
    voice_server_update_cb *on_voice_server_update;
  } cbs;

  int ping_ms; //latency between client and websockets server

  struct discord_user *bot; //the user associated with this client
  struct sized_buffer sb_bot; //@todo this is temporary

  struct discord *p_client; //points to client this struct is a part of

  pthread_mutex_t lock; //for accessing gw fields within events
};

/* GATEWAY PRIVATE FUNCTIONS */
void discord_gateway_init(struct discord_gateway *gw, const char token[]);
void discord_gateway_config_init(struct discord_gateway *gw, const char config_file[]);
void discord_gateway_cleanup(struct discord_gateway *gw);
void discord_gateway_run(struct discord_gateway *gw);
/* gracefully exit the infinite loop */
void discord_gateway_shutdown(struct discord_gateway *gw);

struct _discord_voice { /* PRIVATE VOICE CONNECTION STRUCTURE */
  struct websockets *ws;
  char base_url[MAX_URL_LEN];

  struct discord_gateway_payload payload;

  struct { /* HEARTBEAT STRUCTURE */
    u64_unix_ms_t interval_ms; //fixed interval between heartbeats
    u64_unix_ms_t tstamp; //start pulse timestamp in milliseconds
  } hbeat;

  int ping_ms; //latency between client and websockets server

  pthread_mutex_t lock; //for accessing gw fields within events
  pthread_cond_t cond_server_update; // wait for server update cond
};

#if 0 /* defined at discord.h and discord-voice.c */
struct discord_voice* discord_send_voice_state_update(
  u64_snowflake_t guild_id,
  u64_snowflake_t channel_id,
  bool self_mute,
  bool self_deaf);
void discord_voice_connect(struct discord_voice *vc);
#endif

struct discord {
  struct discord_adapter adapter;
  struct discord_gateway gw;

  struct discord_voice **vcs;
  size_t num_vcs;
  pthread_mutex_t lock; // for synchronizing vcs
  int pending_vcs;

  void *data; //space for user arbitrary data
};

#endif // DISCORD_COMMON_H
