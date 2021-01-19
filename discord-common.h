#ifndef LIBDISCORD_COMMON_H_
#define LIBDISCORD_COMMON_H_

//#include <libdiscord.h> (implicit)

#include <curl/curl.h>
#include "json-scanf.h"

#include "discord-tool-debug.h"

/* UTILITY MACROS */
#define STREQ(str1, str2) (0 == strcmp(str1, str2))
#define STRNEQ(str1, str2, n) (0 == strncmp(str1, str2, n))
//check if string is empty
#define IS_EMPTY_STRING(str) (!(str) || !*(str))
//if case matches return token as string
#define CASE_RETURN_STR(opcode) case opcode: return #opcode

//possible http methods
enum http_method {
  DELETE, GET, POST, PATCH, PUT
};

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

/* HTTP RESPONSE CODES
https://discord.com/developers/docs/topics/opcodes-and-status-codes#http-http-response-codes */
enum http_code {
  HTTP_OK                       = 200,
  HTTP_CREATED                  = 201,
  HTTP_NO_CONTENT               = 204,
  HTTP_NOT_MODIFIED             = 304,
  HTTP_BAD_REQUEST              = 400,
  HTTP_UNAUTHORIZED             = 401,
  HTTP_FORBIDDEN                = 403,
  HTTP_NOT_FOUND                = 404,
  HTTP_METHOD_NOT_ALLOWED       = 405,
  HTTP_TOO_MANY_REQUESTS        = 429,
  HTTP_GATEWAY_UNAVAILABLE      = 502,

  CURL_NO_RESPONSE              = 0,
};

struct api_resbody_s {
  char *str; //the response str
  size_t size; //the response str length
};

#define MAX_HEADER_SIZE 100

struct api_header_s {
  char field[MAX_HEADER_SIZE][MAX_HEADER_LEN];
  char value[MAX_HEADER_SIZE][MAX_HEADER_LEN];
  int size;
};

struct api_route_s {
  char *str; //bucket route
  struct api_bucket_s *p_bucket; //bucket assigned to this route
};

struct api_bucket_s {
  char *hash; //the hash associated with this bucket
  int remaining; //connections this bucket can do before cooldown
  long long reset_after;
  long long reset;
};

struct discord_api_s {
  struct curl_slist *req_header; //the request header sent to the api

  struct api_resbody_s body; //the api response string
  struct api_header_s pairs; //the key/field pairs response header

  struct { /* RATELIMITING STRUCTURE */
    void *root_routes; //check GNU tree functions from search.h

    struct api_bucket_s **buckets;
    size_t num_buckets;
  } ratelimit;

  CURL *ehandle; //the curl's easy handle used to perform requests

  discord_t *p_client; //points to client this struct is a part of
};

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
  WS_DISCONNECTED,  //disconnected from ws
  WS_RESUME,        //attempt to resume ws session
  WS_FRESH,         //attempt a fresh ws session (session timed out)
  WS_CONNECTED,     //connected to ws
};

struct discord_ws_s {
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
    discord_idle_cb *on_idle;   //triggers in every event loop iteration
    discord_idle_cb *on_ready; //triggers when connection first establishes
    struct { /* MESSAGE CALLBACKS STRUCTURE */
      discord_message_cb *create; //triggers when a message is created
      discord_message_cb *update; //triggers when a message is updated (edited)
      discord_message_cb *delete; //triggers when a message is deleted
    } on_message;
  } cbs;

  discord_user_t *self; //the user associated with this client

  discord_t *p_client; //points to client this struct is a part of
};

struct _settings_s { //@todo this whole struct is temporary
  char *token;
  FILE *f_json_dump;
  FILE *f_curl_dump;
};

typedef struct discord_s {
  struct discord_ws_s ws;
  struct discord_api_s api;
  
  void *data; //space for user arbitrary data

  struct _settings_s settings;
} discord_t;

//callback for object to be loaded by api response
typedef void (discord_load_obj_cb)(void *p_obj, char *str, size_t len);

/* discord-utils.c */

void* Discord_utils_set_data(discord_t *client, void *data);
void* Discord_utils_get_data(discord_t *client);
void Discord_utils_json_dump(const char *text, struct _settings_s *settings, const char *data);
int Discord_utils_debug_cb(
    CURL *ehandle,
    curl_infotype type,
    char *data,
    size_t size,
    void *p_userdata);

/* discord-public*.c */

void Discord_guild_load(void *p_guild, char *str, size_t len);
void Discord_user_load(void *p_user, char *str, size_t len);
void Discord_message_load(void *p_message, char *str, size_t len);

/* discord-api.c */

void Discord_api_init(struct discord_api_s *api, char token[]);
void Discord_api_cleanup(struct discord_api_s *api);

void Discord_api_request(
  struct discord_api_s *api, 
  void *p_object, 
  discord_load_obj_cb *load_cb,
  char postfields[], //only for POST/PUT methods
  enum http_method http_method,
  char endpoint[],
  ...);

/* discord-api-ratelimit.c */

long long Discord_ratelimit_delay(struct api_bucket_s *bucket, _Bool use_clock);
char* Discord_ratelimit_route(char endpoint[]);
struct api_bucket_s* Discord_ratelimit_tryget_bucket(struct discord_api_s *api, char *bucket_route);
struct api_bucket_s* Discord_ratelimit_assign_bucket(struct discord_api_s *api, char *bucket_route);
void Discord_ratelimit_parse_header(struct api_bucket_s *bucket, struct api_header_s *pairs);

/* discord-websockets.c */

void Discord_ws_init(struct discord_ws_s *ws, char token[]);
void Discord_ws_cleanup(struct discord_ws_s *ws);

void Discord_ws_setcb_idle(struct discord_ws_s *ws, discord_idle_cb *user_cb);
void Discord_ws_setcb_ready(struct discord_ws_s *ws, discord_idle_cb *user_cb);
void Discord_ws_setcb_message_create(struct discord_ws_s *ws, discord_message_cb *user_cb);
void Discord_ws_setcb_message_update(struct discord_ws_s *ws, discord_message_cb *user_cb);
void Discord_ws_setcb_message_delete(struct discord_ws_s *ws, discord_message_cb *user_cb);

void Discord_ws_run(struct discord_ws_s *ws);

#endif
