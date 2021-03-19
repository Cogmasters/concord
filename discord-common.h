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

namespace discord {
  namespace channel {
    namespace embed {
      namespace thumbnail { struct dati; }
      namespace video = thumbnail;
      namespace image = thumbnail;
    }
  }
}


#include "./specs-code/all_opaque_struct.hh"
#include "./specs-code/all_enums.hh"
#include "./specs-code/all_structs.hh"

namespace discord {

struct client;

namespace adapter {
  namespace bucket { struct dati; }
} // namespace adapter

/* IDLE CALLBACK (runs on every iteration, no trigger required) */
typedef void (idle_cb)(client *client, const user::dati *me);

/* MESSAGE EVENTS CALLBACKS */
typedef void (message_cb)(
    client *client, const user::dati *me, 
    const channel::message::dati *message);
typedef void (sb_message_cb)(
    client *client, const user::dati *me,
    struct sized_buffer sb_me,
    const channel::message::dati *message,
    struct sized_buffer sb_message);
typedef void (message_delete_cb)(
    client *client, const user::dati *me, 
    const u64_snowflake_t id, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t guild_id);
typedef void (message_delete_bulk_cb)(
    client *client, const user::dati *me, 
    const size_t nids, 
    const u64_snowflake_t ids[], 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t guild_id);

/* MESSAGE REACTION EVENTS CALLBACKS */
typedef void (reaction_add_cb)(
    client *client, const user::dati *me, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t message_id, 
    const u64_snowflake_t guild_id, 
    const guild::member::dati *member, 
    const emoji::dati *emoji);
typedef void (reaction_remove_cb)(
    client *client, const user::dati *me, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t message_id, 
    const u64_snowflake_t guild_id, 
    const emoji::dati *emoji);
typedef void (reaction_remove_all_cb)(
    client *client, const user::dati *me, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t message_id, 
    const u64_snowflake_t guild_id);
typedef void (reaction_remove_emoji_cb)(
    client *client, const user::dati *me, 
    const u64_snowflake_t channel_id, 
    const u64_snowflake_t message_id, 
    const u64_snowflake_t guild_id,
    const emoji::dati *emoji);

/* GUILD MEMBER EVENTS CALLBACKS */
typedef void (guild_member_cb)(
    client *client, const user::dati *me, 
    const u64_snowflake_t guild_id, 
    const guild::member::dati *member);
typedef void (guild_member_remove_cb)(
    client *client, const user::dati *me, 
    const u64_snowflake_t guild_id, 
    const user::dati *user);


namespace adapter { /* discord-adapter.cpp */

struct dati { /* ADAPTER STRUCTURE */
  struct user_agent_s ua;

  struct { /* RATELIMITING STRUCTURE */
    bucket::dati **buckets; //active client buckets
    size_t num_buckets; //amount of active client buckets
    
    //check GNU tree functions from search.h
    void *routes_root; //the encountered routes tree's root
  } ratelimit;

  client *p_client; //points to client this struct is a part of
};

void init(dati *adapter, const char token[], const char config_file[]);
void cleanup(dati *adapter);
void run(
  dati *adapter, 
  struct resp_handle *resp_handle,
  struct sized_buffer *req_body, // needed for POST/PUT/PATCH methods
  enum http_method http_method,
  char endpoint[],
  ...);

namespace bucket { /* discord-ratelimit.cpp */
struct dati { /* BUCKET STRUCTURE */
  char *hash; //the hash associated with this bucket
  int remaining; //connections this bucket can do before cooldown
  int64_t reset_after_ms;
  u64_unix_ms_t reset_tstamp;

  u64_unix_ms_t update_tstamp; // last update timestamp
  pthread_mutex_t lock; // used to synchronize buckets
};

void cleanup(adapter::dati *adapter);
void try_cooldown(dati *bucket);
dati* try_get(adapter::dati *adapter, char endpoint[]);
void build(adapter::dati *adapter, dati *bucket, char endpoint[], struct ua_conn_s *conn);

} // namespace bucket
} // namespace adapter

namespace gateway { /* discord-gateway.cpp */

namespace session { /* SESSION START LIMIT STRUCTURE */
struct dati {
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

void dati_from_json(char *str, size_t len, void *p_session);
void get(client *client, dati *p_session);
void get_bot(client *client, dati *p_session);

} // namespace session

struct cmd_cbs {
  char *str;
  message_cb *cb;
};

struct payload_s { /* PAYLOAD STRUCTURE */
  opcodes::code opcode; //field 'op'
  int seq_number; //field 's'
  char event_name[64]; //field 't'
  char event_data[8192]; //field 'd'
};

struct dati { /* GATEWAY STRUCTURE */
  struct websockets_s ws;

  identify::dati *identify;
  char session_id[512]; //the session id (for resuming lost connections)

  struct payload_s payload;

  struct { /* HEARTBEAT STRUCTURE */
    u64_unix_ms_t interval_ms; //fixed interval between heartbeats
    u64_unix_ms_t tstamp; //start pulse timestamp in milliseconds
  } hbeat;

  session::dati session;

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

  user::dati *me; //the user associated with this client
  struct sized_buffer sb_me; //@todo this is temporary for wrapping JS

  client *p_client; //points to client this struct is a part of

  pthread_mutex_t lock; //for accessing gw fields within events
};

void init(dati *gw, const char token[], const char config_file[]);
void cleanup(dati *gw);
void run(dati *gw);
/*
 * gracefully exit the infinite loop
 */
void shutdown(dati *gw);

} // namespace gateway

struct client {
  adapter::dati adapter;
  gateway::dati gw;
  
  void *data; //space for user arbitrary data
};
} // namespace discord

#endif // LIBDISCORD_COMMON_H
