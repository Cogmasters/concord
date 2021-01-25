#ifndef LIBDISCORD_COMMON_H
#define LIBDISCORD_COMMON_H

#include <curl/curl.h>
#include "json-scanf.h"

#include "http-common.h"

/* ENDPOINTS */
#define MESSAGES              "/messages"
#define MESSAGE               MESSAGES"/%s"

#define CHANNELS              "/channels"
#define CHANNEL               CHANNELS"/%s"

#define REACTION_EMOJI        CHANNEL MESSAGE"/reactions/%s"
#define REACTION_EMOJI_USER   REACTION_EMOJI"/%s"

#define PINNED_MESSAGES       CHANNEL"/pins"
#define PINNED_MESSAGE        PINNED_MESSAGES"/%s"

#define GUILDS                "/guilds"
#define GUILD                 GUILDS"/%s"

#define USERS                 "/users"
#define USER                  USERS"/%s"


namespace discord {

struct client; // forward declaration
namespace message { struct data; } // forward declaration
namespace channel { struct data; } // forward declaration
namespace user { struct data; } // forward declaration
namespace guild { struct data; } // forward declaration

typedef void (idle_cb)(discord::client *client, const user::data *self);
typedef void (message_cb)(discord::client *client, const user::data *self, const message::data *message);

namespace user_agent { /* discord-user-agent.cpp */

namespace bucket { struct data; } //forward declaration

struct data {
  struct curl_slist *req_header; //the request header sent to the api

  struct api_resbody_s body; //the api response string
  struct api_header_s pairs; //the key/field pairs response header

  struct { /* RATELIMITING STRUCTURE */
    bucket::data **buckets; //active client buckets
    size_t num_buckets; //amount of active client buckets
    
    //check GNU tree functions from search.h
    void *routes_root; //the encountered routes tree's root
  } ratelimit;

  CURL *ehandle; //the curl's easy handle used to perform requests

  discord::client *p_client; //points to client this struct is a part of
};

void init(user_agent::data *ua, char token[]);
void cleanup(user_agent::data *ua);
void run(
  user_agent::data *ua, 
  void *p_object, 
  load_obj_cb *load_cb,
  char postfields[], //only for POST/PUT methods
  enum http_method http_method,
  char endpoint[],
  ...);

namespace bucket { /* discord-ratelimit.cpp */

struct data {
  char *hash; //the hash associated with this bucket
  int remaining; //connections this bucket can do before cooldown
  long long reset_after_ms;
  long long reset_ms;
};

void cleanup(user_agent::data *ua);
long long cooldown(bucket::data *bucket, bool use_clock);
bucket::data* try_get(user_agent::data *ua, char endpoint[]);
void build(user_agent::data *ua, bucket::data *bucket, char endpoint[]);

} // namespace bucket
} // namespace user_agent

namespace websockets { /* discord-websockets.cpp */

/* GATEWAY CLOSE EVENT CODES
https://discord.com/developers/docs/topics/opcodes-and-status-codes#gateway-gateway-close-event-codes */
enum ws_close_opcodes {
  GATEWAY_CLOSE_REASON_UNKNOWN_ERROR          = 4000,
  GATEWAY_CLOSE_REASON_UNKNOWN_OPCODE         = 4001,
  GATEWAY_CLOSE_REASON_DECODE_ERROR           = 4002,
  GATEWAY_CLOSE_REASON_NOT_AUTHENTICATED      = 4003,
  GATEWAY_CLOSE_REASON_AUTHENTICATION_FAILED  = 4004,
  GATEWAY_CLOSE_REASON_ALREADY_AUTHENTICATED  = 4005,
  GATEWAY_CLOSE_REASON_INVALID_SEQUENCE       = 4007,
  GATEWAY_CLOSE_REASON_RATE_LIMITED           = 4008,
  GATEWAY_CLOSE_REASON_SESSION_TIMED_OUT      = 4009,
  GATEWAY_CLOSE_REASON_INVALID_SHARD          = 4010,
  GATEWAY_CLOSE_REASON_SHARDING_REQUIRED      = 4011,
  GATEWAY_CLOSE_REASON_INVALID_API_VERSION    = 4012,
  GATEWAY_CLOSE_REASON_INVALID_INTENTS        = 4013,
  GATEWAY_CLOSE_REASON_DISALLOWED_INTENTS     = 4014,
};

/* GATEWAY INTENTS
https://discord.com/developers/docs/topics/gateway#identify-identify-structure */
//@todo shorter naming
enum ws_intents {
  WS_INTENT_GUILDS                        = 1 << 0,
  WS_INTENT_GUILD_MEMBERS                 = 1 << 1,
  WS_INTENT_GUILD_BANS                    = 1 << 2,
  WS_INTENT_GUILD_EMOJIS                  = 1 << 3,
  WS_INTENT_GUILD_INTEGRATIONS            = 1 << 4,
  WS_INTENT_GUILD_WEBHOOKS                = 1 << 5,
  WS_INTENT_GUILD_INVITES                 = 1 << 6,
  WS_INTENT_GUILD_VOICE_STATES            = 1 << 7,
  WS_INTENT_GUILD_PRESENCES               = 1 << 8,
  WS_INTENT_GUILD_MESSAGES                = 1 << 9,
  WS_INTENT_GUILD_MESSAGE_REACTIONS       = 1 << 10,
  WS_INTENT_GUILD_MESSAGE_TYPING          = 1 << 11,
  WS_INTENT_DIRECT_MESSAGES               = 1 << 12,
  WS_INTENT_DIRECT_MESSAGE_REACTIONS      = 1 << 13,
  WS_INTENT_DIRECT_MESSAGE_TYPING         = 1 << 14,
};

/* GATEWAY OPCODES
https://discord.com/developers/docs/topics/opcodes-and-status-codes#gateway-gateway-opcodes */
enum ws_opcodes {
  GATEWAY_DISPATCH              = 0,
  GATEWAY_HEARTBEAT             = 1,
  GATEWAY_IDENTIFY              = 2,
  GATEWAY_PRESENCE_UPDATE       = 3,
  GATEWAY_VOICE_STATE_UPDATE    = 4,
  GATEWAY_RESUME                = 6,
  GATEWAY_RECONNECT             = 7,
  GATEWAY_REQUEST_GUILD_MEMBERS = 8,
  GATEWAY_INVALID_SESSION       = 9,
  GATEWAY_HELLO                 = 10,
  GATEWAY_HEARTBEAT_ACK         = 11,
};

enum ws_status {
  DISCONNECTED,  //disconnected from ws
  RESUME,        //attempt to resume ws session
  FRESH,         //attempt a fresh ws session (session timed out)
  CONNECTED,     //connected to ws
};

struct data {
  enum ws_status status; //connection to discord status
  int reconnect_attempts; //hard limit 5 reconnection attempts @todo make configurable

  char *identify; //the identify payload (for establishing a new connection)
  char *session_id; //the session id (for resuming lost connections)

  CURLM *mhandle;
  CURL *ehandle;

  struct { /* PAYLOAD STRUCTURE */
    enum ws_opcodes opcode; //field 'op'
    int seq_number; //field 's'
    char event_name[16]; //field 't'
    char event_data[8192]; //field 'd'
  } payload;

  struct { /* HEARTBEAT STRUCTURE */
    long interval_ms; //interval between heartbeats
    long start_ms; //start pulse in milliseconds
  } hbeat;

  struct { /* CALLBACKS STRUCTURE */
    idle_cb *on_idle;   //triggers in every event loop iteration
    idle_cb *on_ready; //triggers when connection first establishes
    struct { /* MESSAGE CALLBACKS STRUCTURE */
      message_cb *create; //triggers when a message is created
      message_cb *update; //triggers when a message is updated (edited)
      message_cb *del; //triggers when a message is deleted
    } on_message;
  } cbs;

  user::data *self; //the user associated with this client

  discord::client *p_client; //points to client this struct is a part of
};

void init(websockets::data *ws, char token[]);
void cleanup(websockets::data *ws);
void run(websockets::data *ws);

} // namespace websockets

struct client {
  websockets::data ws;
  user_agent::data ua;
  
  void *data; //space for user arbitrary data

  struct _settings_s settings;
};

} // namespace discord

#endif // LIBDISCORD_COMMON_H
