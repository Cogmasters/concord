#ifndef LIBDISCORD_COMMON_H
#define LIBDISCORD_COMMON_H

#include <curl/curl.h>
#include "json-scanf.h"

#include "http-common.h"


namespace discord {

struct client; // forward declaration
namespace channel { // forward declaration
  struct dati; 
  namespace message { struct dati; }
} // namespace channel
namespace user { struct dati; } // forward declaration
namespace guild { // forward declaration
  struct dati; 
  namespace member { struct dati; }
} // namespace guild

typedef void (idle_cb)(discord::client *client, const user::dati *me);
typedef void (message_cb)(discord::client *client, const user::dati *me, const channel::message::dati *message);
typedef void (message_delete_cb)(discord::client *client, const user::dati *me, const uint64_t id, const uint64_t channel_id, const uint64_t guild_id);
typedef void (message_delete_bulk_cb)(discord::client *client, const user::dati *me, const size_t nids, const uint64_t ids[], const uint64_t channel_id, const uint64_t guild_id);
typedef void (guild_member_cb)(discord::client *client, const user::dati *me, const uint64_t guild_id, const guild::member::dati *member);
typedef void (guild_member_remove_cb)(discord::client *client, const user::dati *me, const uint64_t guild_id, const user::dati *user);

namespace user_agent { /* discord-user-agent.cpp */

namespace bucket { struct dati; } //forward declaration

struct dati { /* USER AGENT STRUCTURE */
  struct curl_slist *req_header; //the request header sent to the api

  struct sized_buffer resp_body; //the api response string
  struct api_header_s pairs; //the key/field pairs response header

  struct { /* RATELIMITING STRUCTURE */
    bucket::dati **buckets; //active client buckets
    size_t num_buckets; //amount of active client buckets
    
    //check GNU tree functions from search.h
    void *routes_root; //the encountered routes tree's root
  } ratelimit;

  CURL *ehandle; //the curl's easy handle used to perform requests

  discord::client *p_client; //points to client this struct is a part of
};

void init(user_agent::dati *ua, char token[]);
void cleanup(user_agent::dati *ua);
void run(
  user_agent::dati *ua, 
  struct resp_handle *resp_handle,
  struct sized_buffer *req_body, // needed for POST/PUT/PATCH methods
  enum http_method http_method,
  char endpoint[],
  ...);

namespace bucket { /* discord-ratelimit.cpp */

struct dati { /* BUCKET STRUCTURE */
  char *hash; //the hash associated with this bucket
  int remaining; //connections this bucket can do before cooldown
  long long reset_after_ms;
  long long reset_ms;
};

void cleanup(user_agent::dati *ua);
void try_cooldown(bucket::dati *bucket);
bucket::dati* try_get(user_agent::dati *ua, char endpoint[]);
void build(user_agent::dati *ua, bucket::dati *bucket, char endpoint[]);

} // namespace bucket
} // namespace user_agent

namespace websockets { /* discord-websockets.cpp */

/* GATEWAY CLOSE EVENT CODES
https://discord.com/developers/docs/topics/opcodes-and-status-codes#gateway-gateway-close-event-codes */
enum close_opcodes {
  CLOSE_REASON_UNKNOWN_ERROR          = 4000,
  CLOSE_REASON_UNKNOWN_OPCODE         = 4001,
  CLOSE_REASON_DECODE_ERROR           = 4002,
  CLOSE_REASON_NOT_AUTHENTICATED      = 4003,
  CLOSE_REASON_AUTHENTICATION_FAILED  = 4004,
  CLOSE_REASON_ALREADY_AUTHENTICATED  = 4005,
  CLOSE_REASON_INVALID_SEQUENCE       = 4007,
  CLOSE_REASON_RATE_LIMITED           = 4008,
  CLOSE_REASON_SESSION_TIMED_OUT      = 4009,
  CLOSE_REASON_INVALID_SHARD          = 4010,
  CLOSE_REASON_SHARDING_REQUIRED      = 4011,
  CLOSE_REASON_INVALID_API_VERSION    = 4012,
  CLOSE_REASON_INVALID_INTENTS        = 4013,
  CLOSE_REASON_DISALLOWED_INTENTS     = 4014
};

/* GATEWAY INTENTS
https://discord.com/developers/docs/topics/gateway#identify-identify-structure */
struct intents { // pre c++11 enum class
  enum {
    GUILDS                        = 1 << 0,
    GUILD_MEMBERS                 = 1 << 1,
    GUILD_BANS                    = 1 << 2,
    GUILD_EMOJIS                  = 1 << 3,
    GUILD_INTEGRATIONS            = 1 << 4,
    GUILD_WEBHOOKS                = 1 << 5,
    GUILD_INVITES                 = 1 << 6,
    GUILD_VOICE_STATES            = 1 << 7,
    GUILD_PRESENCES               = 1 << 8,
    GUILD_MESSAGES                = 1 << 9,
    GUILD_MESSAGE_REACTIONS       = 1 << 10,
    GUILD_MESSAGE_TYPING          = 1 << 11,
    DIRECT_MESSAGES               = 1 << 12,
    DIRECT_MESSAGE_REACTIONS      = 1 << 13,
    DIRECT_MESSAGE_TYPING         = 1 << 14
  };
};

/* GATEWAY OPCODES
https://discord.com/developers/docs/topics/opcodes-and-status-codes#gateway-gateway-opcodes */
struct opcodes {
  enum {
    DISPATCH              = 0,
    HEARTBEAT             = 1,
    IDENTIFY              = 2,
    PRESENCE_UPDATE       = 3,
    VOICE_STATE_UPDATE    = 4,
    RESUME                = 6,
    RECONNECT             = 7,
    REQUEST_GUILD_MEMBERS = 8,
    INVALID_SESSION       = 9,
    HELLO                 = 10,
    HEARTBEAT_ACK         = 11
  };
};

struct status {
  enum {
    DISCONNECTED,  //disconnected from ws
    RESUME,        //attempt to resume ws session
    FRESH,         //attempt a fresh ws session (session timed out)
    CONNECTED     //connected to ws
  };
};

struct dati { /* WEBSOCKETS STRUCTURE */
  int status; //connection to discord status
  int reconnect_attempts; //hard limit 5 reconnection attempts @todo make configurable

  char *identify; //the identify payload (for establishing a new connection)
  int intents; //the gateway events to be listened to
  char session_id[512]; //the session id (for resuming lost connections)

  CURLM *mhandle;
  CURL *ehandle;

  struct { /* PAYLOAD STRUCTURE */
    int opcode; //field 'op'
    int seq_number; //field 's'
    char event_name[64]; //field 't'
    char event_data[8192]; //field 'd'
  } payload;

  struct { /* HEARTBEAT STRUCTURE */
    long interval_ms; //fixed interval between heartbeats
    long tstamp; //start pulse timestamp in milliseconds
  } hbeat;

  struct { /* SESSION START LIMIT STRUCTURE */
    char url[MAX_URL_LEN];
    int shards;

    int total;
    int remaining;
    int reset_after;
    int max_concurrency; //max concurrent sessions we can handle

    int concurrent; //active concurrent sessions
    long identify_tstamp; //identify timestamp in ms

    long event_tstamp; //event timestamp in ms (resets every 60s)
    int event_count; //count elements to avoid reaching 120/60sec limit
  } session;

  struct { /* CALLBACKS STRUCTURE */
    idle_cb *on_idle;   //triggers in every event loop iteration
    idle_cb *on_ready; //triggers when connection first establishes
    struct { /* MESSAGE CALLBACKS STRUCTURE */
      message_cb *create; //triggers when a message is created
      message_cb *update; //triggers when a message is updated (edited)
      message_delete_cb *del; //triggers when a message is deleted
      message_delete_bulk_cb *delete_bulk; //triggers when multiple messages are deleted at once
    } on_message;
    struct { /* GUILD MEMBER CALLBACKS STRUCTURE */
      guild_member_cb *add; //triggers when a member joins a guild
      guild_member_cb *update; //triggers when a member is updated
      guild_member_remove_cb *remove; //triggers when a member leaves or is removed a guild
    } on_guild_member;
  } cbs;

  long long now_tstamp; //timestamp updated every loop iteration

  int ping_ms; //latency between client and websockets server

  user::dati *me; //the user associated with this client

  discord::client *p_client; //points to client this struct is a part of
};

void init(websockets::dati *ws, char token[]);
void cleanup(websockets::dati *ws);
void run(websockets::dati *ws);

} // namespace websockets

struct client {
  websockets::dati ws;
  user_agent::dati ua;
  
  void *data; //space for user arbitrary data

  struct _settings_s settings;
};

} // namespace discord

#endif // LIBDISCORD_COMMON_H
