#ifndef LIBDISCORD_COMMON_H
#define LIBDISCORD_COMMON_H

#include <inttypes.h>
#include <curl/curl.h>
#include "json-scanf.h"
#include "json-actor.h"

#include "user-agent.h"
#include "orka-utils.h"

namespace discord {

/* * * * * * * * * * * * * * * * * * * * */
/* FORWARD DECLARATION OF EVERY DATATYPE */

struct client;
namespace audit_log {
  struct dati;
  namespace entry { 
    struct dati; 
    namespace events { typedef int code; }
    namespace optional_info { struct dati; }
  }
  namespace change { struct dati; }
  namespace key { struct dati; }
} // namespace audit_log
namespace channel {
  struct dati; 
  namespace types { typedef int code; }
  namespace message { 
    struct dati; 
    namespace types { typedef int code; }
    namespace activity { 
      struct dati; 
      namespace types { typedef int code; }
    } // namespace activity
    namespace application { struct dati; }
    namespace reference { struct dati; }
    namespace flags { typedef int code; }
    namespace sticker {
      struct dati;
      namespace format_types { typedef int code; }
    } // namespace sticker
  } // namespace message
  namespace followed_channel { struct dati; }
  namespace reaction { struct dati; }
  namespace overwrite { struct dati; }
  namespace embed { 
    struct dati; 
    namespace thumbnail { struct dati; }
    namespace video = thumbnail;
    namespace image = thumbnail;
    namespace provider { struct dati; }
    namespace author { struct dati; }
    namespace footer { struct dati; }
    namespace field { struct dati; }
  } // namespace embed
  namespace attachment { struct dati; }
  namespace mention { struct dati; }
  namespace allowed_mentions { struct dati; }
} // namespace channel
namespace emoji { struct dati; }
namespace guild {
  struct dati; 
  namespace default_message_notification_level { typedef int code; }
  namespace explicit_content_filter_level { typedef int code; }
  namespace mfa_level { typedef int code; }
  namespace verification_level { typedef int code; }
  namespace premium_tier { typedef int code; }
  namespace system_channel_flags { typedef int code; }
  namespace guild_features { typedef int code; }
  namespace unavailable_guild { struct dati; }
  namespace preview { struct dati; }
  namespace widget { struct dati; }
  namespace member { struct dati; }
  namespace integration { 
    struct dati; 
    //namespace expire_behaviors { typedef int code; }
    //namespace account { struct dati; }
    //namespace application { struct dati; }
  } // namespace integration
  namespace ban { struct dati; }
  namespace welcome_screen { 
    struct dati; 
    namespace screen_channel { struct dati; }
  } // namespace welcome_screen
  namespace membership_screening {
    struct dati;
    namespace field {
      struct dati;
      namespace field_type { typedef int code; }
    } // namespace field
  } // namespace membsership_screening
} // namespace guild
namespace invite {
  struct dati;
  //namespace target_user_types { typedef int code; }
  namespace metadata { struct dati; }
} // namespace invite
namespace Template { struct dati; }
namespace user { 
  struct dati; 
  //namespace flags { typedef int code; }
  //namespace premium_types { typedef int code; }
  namespace connection {
    struct dati;
    //namespace visibility_types { typedef int code; }
  } // namespace connection
} // namespace user
namespace voice {
  struct dati;
  namespace region { struct dati; }
} // namespace voice
namespace webhook {
  struct dati;
  //namespace types { enum code; }
} // namespace webhook

namespace user_agent {
  namespace bucket { struct dati; }
} // namespace user_agent

namespace websockets {
  namespace identify {
    namespace status_update {
      struct dati;
      namespace activity { 
        struct dati;
        namespace types { typedef int code; }
      } // namespace activity
    } // namespace status_update
  } // namespace identify
  struct dati;
  namespace intents { typedef int code; }
  namespace opcodes { typedef int code; }
  namespace status { typedef int code; }
} // namespace websockets

/* * * * END OF FORWARD DECLARATION * * * */
/* * * * * * * * * * * * * * * * * * * * */

/* IDLE CALLBACK (runs on every iteration, no trigger required) */
typedef void (idle_cb)(client *client, const user::dati *me);

/* MESSAGE EVENTS CALLBACKS */
typedef void (message_cb)(client *client, const user::dati *me, 
    const channel::message::dati *message);
typedef void (message_delete_cb)(client *client, const user::dati *me, 
    const uint64_t id, 
    const uint64_t channel_id, 
    const uint64_t guild_id);
typedef void (message_delete_bulk_cb)(client *client, const user::dati *me, 
    const size_t nids, 
    const uint64_t ids[], 
    const uint64_t channel_id, 
    const uint64_t guild_id);

/* MESSAGE REACTION EVENTS CALLBACKS */
typedef void (reaction_add_cb)(client *client, const user::dati *me, 
    const uint64_t channel_id, 
    const uint64_t message_id, 
    const uint64_t guild_id, 
    const guild::member::dati *member, 
    const emoji::dati *emoji);
typedef void (reaction_remove_cb)(client *client, const user::dati *me, 
    const uint64_t channel_id, 
    const uint64_t message_id, 
    const uint64_t guild_id, 
    const emoji::dati *emoji);
typedef void (reaction_remove_all_cb)(client *client, const user::dati *me, 
    const uint64_t channel_id, 
    const uint64_t message_id, 
    const uint64_t guild_id);
typedef void (reaction_remove_emoji_cb)(client *client, const user::dati *me, 
    const uint64_t channel_id, 
    const uint64_t message_id, 
    const uint64_t guild_id,
    const emoji::dati *emoji);

/* GUILD MEMBER EVENTS CALLBACKS */
typedef void (guild_member_cb)(client *client, const user::dati *me, 
    const uint64_t guild_id, 
    const guild::member::dati *member);
typedef void (guild_member_remove_cb)(client *client, const user::dati *me, 
    const uint64_t guild_id, 
    const user::dati *user);


namespace user_agent { /* discord-user-agent.cpp */

/* JSON ERROR CODE STRUCTURE
https://discord.com/developers/docs/topics/opcodes-and-status-codes#json-json-error-codes */
struct error { /* @todo this won't be thread safe. */
  int code; //last error code received
  char message[256]; //meaning of the error received
};

struct dati { /* USER AGENT STRUCTURE */
  struct user_agent_s common;

  struct { /* RATELIMITING STRUCTURE */
    bucket::dati **buckets; //active client buckets
    size_t num_buckets; //amount of active client buckets
    
    //check GNU tree functions from search.h
    void *routes_root; //the encountered routes tree's root
  } ratelimit;

  /* stores last json error detected, fields are reseted after
   *  get_json_error() is called */
  struct error json_err;

  client *p_client; //points to client this struct is a part of
};

void init(dati *ua, const char token[], const char config_file[]);
void cleanup(dati *ua);
void run(
  dati *ua, 
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
  uint64_t reset_tstamp;
};

void cleanup(user_agent::dati *ua);
void try_cooldown(dati *bucket);
dati* try_get(user_agent::dati *ua, char endpoint[]);
void build(user_agent::dati *ua, dati *bucket, char endpoint[], struct ua_conn_s *conn);

} // namespace bucket
} // namespace user_agent

namespace websockets { /* discord-websockets.cpp */

/* GATEWAY CLOSE EVENT CODES
https://discord.com/developers/docs/topics/opcodes-and-status-codes#gateway-gateway-close-event-codes */
enum close_opcodes {
  CLOSE_REASON_UNKNOWN_ERROR         = 4000,
  CLOSE_REASON_UNKNOWN_OPCODE        = 4001,
  CLOSE_REASON_DECODE_ERROR          = 4002,
  CLOSE_REASON_NOT_AUTHENTICATED     = 4003,
  CLOSE_REASON_AUTHENTICATION_FAILED = 4004,
  CLOSE_REASON_ALREADY_AUTHENTICATED = 4005,
  CLOSE_REASON_INVALID_SEQUENCE      = 4007,
  CLOSE_REASON_RATE_LIMITED          = 4008,
  CLOSE_REASON_SESSION_TIMED_OUT     = 4009,
  CLOSE_REASON_INVALID_SHARD         = 4010,
  CLOSE_REASON_SHARDING_REQUIRED     = 4011,
  CLOSE_REASON_INVALID_API_VERSION   = 4012,
  CLOSE_REASON_INVALID_INTENTS       = 4013,
  CLOSE_REASON_DISALLOWED_INTENTS    = 4014
};

/* GATEWAY INTENTS
https://discord.com/developers/docs/topics/gateway#identify-identify-structure */
namespace intents {
enum {
  GUILDS                   = 1 << 0,
  GUILD_MEMBERS            = 1 << 1,
  GUILD_BANS               = 1 << 2,
  GUILD_EMOJIS             = 1 << 3,
  GUILD_INTEGRATIONS       = 1 << 4,
  GUILD_WEBHOOKS           = 1 << 5,
  GUILD_INVITES            = 1 << 6,
  GUILD_VOICE_STATES       = 1 << 7,
  GUILD_PRESENCES          = 1 << 8,
  GUILD_MESSAGES           = 1 << 9,
  GUILD_MESSAGE_REACTIONS  = 1 << 10,
  GUILD_MESSAGE_TYPING     = 1 << 11,
  DIRECT_MESSAGES          = 1 << 12,
  DIRECT_MESSAGE_REACTIONS = 1 << 13,
  DIRECT_MESSAGE_TYPING    = 1 << 14
};
} // namespace intents

/* GATEWAY OPCODES
https://discord.com/developers/docs/topics/opcodes-and-status-codes#gateway-gateway-opcodes */
namespace opcodes {
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
} // namespace opcodes

namespace status {
enum {
  DISCONNECTED,  //disconnected from ws
  RESUME,        //attempt to resume ws session
  FRESH,         //attempt a fresh ws session (session timed out)
  CONNECTED      //connected to ws
};
} // namespace status

namespace session { /* SESSION START LIMIT STRUCTURE */
struct dati {
  char url[MAX_URL_LEN];
  int shards;

  int total;
  int remaining;
  int reset_after;
  int max_concurrency; //max concurrent sessions we can handle

  int concurrent; //active concurrent sessions
  uint64_t identify_tstamp; //identify timestamp in ms

  uint64_t event_tstamp; //event timestamp in ms (resets every 60s)
  int event_count; //count elements to avoid reaching 120/60sec limit
};

void dati_from_json(char *str, size_t len, void *p_session);
void get(client *client, dati *p_session);
void get_bot(client *client, dati *p_session);

} // namespace session

/* IDENTIFY STRUCTURE
https://discord.com/developers/docs/topics/gateway#identify-identify-structure */
namespace identify {

struct dati {
  char *token;
  bool compress;
  int large_threshold;
  int shard[2];
  status_update::dati *presence;
  bool guild_subscriptions;
  intents::code intents;
};

void dati_init(void *p_identify);
dati* dati_alloc();
void dati_cleanup(void *p_identify);
void dati_free(dati *identify);
void dati_from_json(char *str, size_t len, void *p_identify);
int dati_to_json(char *str, size_t len, void *p_identify);

/* GATEWAY STATUS UPDATE STRUCTURE ( aka PRESENCE )
https://discord.com/developers/docs/topics/gateway#update-status-gateway-status-update-structure */
namespace status_update {

struct dati {
  uint64_t since;
  activity::dati **activities;
  char status[16];
  bool afk;
};

void dati_init(void *p_status_update);
dati* dati_alloc();
void dati_cleanup(void *p_status_update);
void dati_free(dati *status_update);
void dati_from_json(char *str, size_t len, void *p_status_update);
int dati_to_json(char *str, size_t len, void *p_status_update);

/* ACTIVITY STRUCTURE
https://discord.com/developers/docs/topics/gateway#activity-object-activity-structure */
namespace activity {

struct dati {
  char name[512];
  types::code type;
  char url[MAX_URL_LEN];
  uint64_t created_at;
  //@todo missing timestamps;
  uint64_t application_id;
  char *details; //@todo find fixed size limit
  char *state; // @todo find fixed size limit
  //@todo missing activity emoji;
  //@todo missing party;
  //@todo missing assets;
  //@todo missing secrets;
  bool instance;
  //@todo missing flags;
};

void dati_init(void *p_activity);
dati* dati_alloc();
void dati_cleanup(void *p_activity);
void dati_free(dati *activity);
void dati_from_json(char *str, size_t len, void *p_activity);
void dati_list_from_json(char *str, size_t len, void *p_activities);
size_t dati_to_json(char *str, size_t len, void *p_activity);
int dati_list_to_json(char *str, size_t len, void *p_activities);

/* ACTIVITY TYPES
https://discord.com/developers/docs/topics/gateway#activity-object-activity-types */
namespace types {
enum {
  GAME      = 0,
  STREAMING = 1,
  LISTENING = 2,
  CUSTOM    = 4,
  COMPETING = 5
};
} // namespace types

} // namespace activity

} // namespace status_update

} // namespace identify

struct cmd_cbs {
  char *str;
  message_cb *cb;
};

struct dati { /* WEBSOCKETS STRUCTURE */
  struct orka_config config;
  status::code status; //connection to discord status
  int reconnect_attempts; //hard limit 5 reconnection attempts @todo make configurable

  identify::dati *identify;
  char session_id[512]; //the session id (for resuming lost connections)

  CURLM *mhandle;
  CURL *ehandle;

  struct { /* PAYLOAD STRUCTURE */
    opcodes::code opcode; //field 'op'
    int seq_number; //field 's'
    char event_name[64]; //field 't'
    char event_data[8192]; //field 'd'
  } payload;

  struct { /* HEARTBEAT STRUCTURE */
    uint64_t interval_ms; //fixed interval between heartbeats
    uint64_t tstamp; //start pulse timestamp in milliseconds
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

  uint64_t now_tstamp; //timestamp updated every loop iteration

  int ping_ms; //latency between client and websockets server

  user::dati *me; //the user associated with this client

  client *p_client; //points to client this struct is a part of
};

void init(dati *ws, const char token[], const char config_file[]);
void cleanup(dati *ws);
void run(dati *ws);

} // namespace websockets

struct client {
  websockets::dati ws;
  user_agent::dati ua;
  
  void *data; //space for user arbitrary data
};

} // namespace discord

#endif // LIBDISCORD_COMMON_H
