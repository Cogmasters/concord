#ifndef LIBDISCORD_COMMON_H
#define LIBDISCORD_COMMON_H

#include <inttypes.h>
#include <curl/curl.h>
#include "json-scanf.h"
#include "json-actor.h"
#include "json-actor-boxed.h"

#include "user-agent.h"
#include "websockets.h"
#include "orka-utils.h"

/* Size limits encountered in the Docs and searching the web */
#define MAX_NAME_LEN          100 + 1
#define MAX_TOPIC_LEN         1024 + 1
#define MAX_DESCRIPTION_LEN   2048 + 1
#define MAX_USERNAME_LEN      32 + 1
#define MAX_DISCRIMINATOR_LEN 4 + 1
#define MAX_SHA256_LEN        1024 + 1
#define MAX_LOCALE_LEN        16 + 1
#define MAX_EMAIL_LEN         254 + 1
#define MAX_REGION_LEN        16 + 1
#define MAX_REASON_LEN        512 + 1
#define MAX_MESSAGE_LEN       2000 + 1
#define MAX_PAYLOAD_LEN       4096 + 1

/* EMBED LIMITS
https://discord.com/developers/docs/resources/channel#embed-limits */
#define EMBED_TITLE_LEN       256 + 1
#define EMBED_DESCRIPTION_LEN 2048 + 1
#define EMBED_MAX_FIELDS      25
#define EMBED_FIELD_NAME_LEN  256 + 1
#define EMBED_FIELD_VALUE_LEN 1024 + 1
#define EMBED_FOOTER_TEXT_LEN 2048 + 1
#define EMBED_AUTHOR_NAME_LEN 256 + 1

/* WEBHOOK LIMITS
https://discord.com/developers/docs/resources/webhook#create-webhook */
#define WEBHOOK_NAME_LEN 80 + 1

/* SNOWFLAKES
https://discord.com/developers/docs/reference#snowflakes */
#define SNOWFLAKE_INCREMENT           12
#define SNOWFLAKE_PROCESS_ID          17
#define SNOWFLAKE_INTERNAL_WORKER_ID  22
#define SNOWFLAKE_TIMESTAMP           64


typedef uint64_t u64_unix_ms_t;
typedef uint64_t u64_snowflake_t;


#include "./specs-code/all_opaque_struct.h"
#include "./specs-code/all_enums.h"
#include "./specs-code/all_structs.h"


/* IDLE CALLBACK (runs on every iteration, no trigger required) */
typedef void (idle_cb)(struct discord_client *client, const struct discord_user_dati *me);

/* MESSAGE EVENTS CALLBACKS */
typedef void (message_cb)(
    struct discord_client *client, const struct discord_user_dati *me, 
    const struct discord_channel_message_dati *message);
typedef void (sb_message_cb)(
    struct discord_client *client, const struct discord_user_dati *me,
    struct sized_buffer sb_me,
    const struct discord_channel_message_dati *message,
    struct sized_buffer sb_message);
typedef void (message_delete_cb)(
    struct discord_client *client, const struct discord_user_dati *me, 
    const u64_snowflake_t id, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t guild_id);
typedef void (message_delete_bulk_cb)(
    struct discord_client *client, const struct discord_user_dati *me, 
    const size_t nids, 
    const u64_snowflake_t ids[], 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t guild_id);

/* MESSAGE REACTION EVENTS CALLBACKS */
typedef void (reaction_add_cb)(
    struct discord_client *client, const struct discord_user_dati *me, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t message_id, 
    const u64_snowflake_t guild_id, 
    const struct discord_guild_member_dati *member, 
    const struct discord_emoji_dati *emoji);
typedef void (reaction_remove_cb)(
    struct discord_client *client, const struct discord_user_dati *me, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t message_id, 
    const u64_snowflake_t guild_id, 
    const struct discord_emoji_dati *emoji);
typedef void (reaction_remove_all_cb)(
    struct discord_client *client, const struct discord_user_dati *me, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t message_id, 
    const u64_snowflake_t guild_id);
typedef void (reaction_remove_emoji_cb)(
    struct discord_client *client, const struct discord_user_dati *me, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t message_id, 
    const u64_snowflake_t guild_id,
    const struct discord_emoji_dati *emoji);

/* GUILD MEMBER EVENTS CALLBACKS */
typedef void (guild_member_cb)(
    struct discord_client *client, const struct discord_user_dati *me, 
    const u64_snowflake_t guild_id, 
    const struct discord_guild_member_dati *member);
typedef void (guild_member_remove_cb)(
    struct discord_client *client, const struct discord_user_dati *me, 
    const u64_snowflake_t guild_id, 
    const struct discord_user_dati *user);


struct discord_adapter {
  struct user_agent_s ua;

  struct { /* RATELIMITING STRUCTURE */
    struct discord_bucket **bucket_pool; //active client buckets
    size_t num_buckets; //amount of active client buckets
    
    //check GNU tree functions from search.h
    void *routes_root; //the encountered routes tree's root
  } ratelimit;

  struct discord_client *p_client; //points to client this struct is a part of

  pthread_mutex_t lock; // used when increasing/fetching buckets
};

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

void discord_bucket_cleanup(struct discord_adapter *bucket);
void discord_bucket_try_cooldown(struct discord_bucket *bucket);
struct discord_bucket* discord_bucket_try_get(struct discord_adapter *adapter, char endpoint[]);
void discord_bucket_build(struct discord_adapter *adapter, struct discord_bucket *bucket, char endpoint[], struct ua_conn_s *conn);

struct discord_session {
  char url[MAX_URL_LEN];
  int shards;

  int total;
  int remaining;
  int reset_after;
  int max_concurrency; //max concurrent sessions we can handle

  int concurrent; //active concurrent sessions
  u64_unix_ms_t identify_tstamp; //identify timestamp in ms

  u64_unix_ms_t event_tstamp; //event timestamp in ms (resets every 60s)
  int event_count; //count elements to avoid reaching 120/60sec limit
};

struct cmd_cbs {
  char *str;
  message_cb *cb;
};

struct payload_s { /* PAYLOAD STRUCTURE */
  enum discord_gateway_opcodes_code opcode; //field 'op'
  int seq_number; //field 's'
  char event_name[64]; //field 't'
  char event_data[8192]; //field 'd'
};

struct discord_gateway { /* GATEWAY STRUCTURE */
  struct websockets_s ws;

  struct discord_gateway_identify_dati *identify;
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

  struct discord_user_dati *me; //the user associated with this client
  struct sized_buffer sb_me; //@todo this is temporary for wrapping JS

  struct discord_client *p_client; //points to client this struct is a part of

  pthread_mutex_t lock; //for accessing gw fields within events
};

void discord_gateway_init(struct discord_gateway *gw, const char token[], const char config_file[]);
void discord_gateway_cleanup(struct discord_gateway *gw);
void discord_gateway_run(struct discord_gateway *gw);
/* gracefully exit the infinite loop */
void discord_gateway_shutdown(struct discord_gateway *gw);

struct discord_client {
  struct discord_adapter adapter;
  struct discord_gateway gw;
  void *data; //space for user arbitrary data
};

#endif // LIBDISCORD_COMMON_H
