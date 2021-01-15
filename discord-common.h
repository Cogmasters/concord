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

enum http_method {
  DELETE,
  GET,
  POST,
  PATCH,
  PUT,
};

/* ENDPOINTS */
#define CHANNEL           "/channels/%s"
#define CHANNEL_MESSAGES  CHANNEL"/messages"

#define GUILD             "/guilds/%s"
#define GUILD_CHANNELS    GUILD"/channels"

#define USER              "/users/%s"
#define USER_GUILDS       USER"/guilds"

/* HTTP RESPONSE CODES
https://discord.com/developers/docs/topics/opcodes-and-status-codes#http-http-response-codes */
enum api_http_code {
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

struct api_response_s {
  char *str; //the response str
  size_t size; //the response str length
};

#define MAX_HEADER_SIZE 1000

struct api_header_s {
  char *key[MAX_HEADER_SIZE];
  char *field[MAX_HEADER_SIZE];
  int size;
};

struct discord_api_s {
  CURL *ehandle; //the curl's easy handle used to perform requests
  struct curl_slist *req_header; //the request header sent to the api
  struct api_response_s res_body; //the api response string
  struct api_header_s res_pairs; //the key/field pairs response header

  discord_t *p_client; //points to client this struct is a part of
};

/* GATEWAY CLOSE EVENT CODES
https://discord.com/developers/docs/topics/opcodes-and-status-codes#gateway-gateway-close-event-codes */
enum ws_close_code {
  WS_CLOSE_UNKNOWN_ERROR          = 4000,
  WS_CLOSE_UNKNOWN_OPCODE         = 4001,
  WS_CLOSE_DECODE_ERROR           = 4002,
  WS_CLOSE_NOT_AUTHENTICATED      = 4003,
  WS_CLOSE_AUTHENTICATION_FAILED  = 4004,
  WS_CLOSE_ALREADY_AUTHENTICATED  = 4005,
  WS_CLOSE_INVALID_SEQUENCE       = 4007,
  WS_CLOSE_RATE_LIMITED           = 4008,
  WS_CLOSE_SESSION_TIMED_OUT      = 4009,
  WS_CLOSE_INVALID_SHARD          = 4010,
  WS_CLOSE_SHARDING_REQUIRED      = 4011,
  WS_CLOSE_INVALID_API_VERSION    = 4012,
  WS_CLOSE_INVALID_INTENTS        = 4013,
  WS_CLOSE_DISALLOWED_INTENTS     = 4014,
};

/* GATEWAY INTENTS
https://discord.com/developers/docs/topics/gateway#identify-identify-structure */
enum ws_intents {
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
  DIRECT_MESSAGE_TYPING         = 1 << 14,
};

/* GATEWAY DISPATCH EVENT CODES
https://discord.com/developers/docs/topics/opcodes-and-status-codes#gateway-gateway-opcodes */
enum ws_dispatch_code {
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
  WS_DISCONNECTED, //connected to ws
  WS_RECONNECTING, //attempting reconnection to ws
  WS_CONNECTED,    //disconnected from ws
};

struct discord_ws_s {
  enum ws_status status;
  int reconnect_attempts; //hard limit 5 reconnection attempts @todo make configurable

  char *identify;
  char *session_id;

  CURLM *mhandle;
  CURL *ehandle;

  struct { /* PAYLOAD STRUCTURE */
    enum ws_dispatch_code opcode; //field 'op'
    int seq_number; //field 's'
    char event_name[16]; //field 't'
    char event_data[8192]; //field 'd'
  } payload;

  struct { /* HEARTBEAT STRUCTURE */
    long interval_ms; //interval between heartbeats
    long start_ms; //start pulse in milliseconds
  } hbeat;

  struct { /* CALLBACKS STRUCTURE */
    discord_idle_cb *on_idle;   /* ON IDLE CB */
    discord_idle_cb *on_ready; /* ON READY CB */
    struct { /* MESSAGE CALLBACKS STRUCTURE */
      discord_message_cb *create; /* ON MESSAGE_CREATE CB */
      discord_message_cb *update; /* ON MESSAGE_UPDATE CB */
      discord_message_cb *delete; /* ON MESSAGE_DELETE CB */
    } on_message;
  } cbs;

  discord_user_t *self;

  discord_t *p_client; //points to client this struct is a part of
};

struct _settings_s { //@todo this whole struct is temporary
  char *token;
  FILE *f_json_dump;
  FILE *f_curl_dump;
};

typedef struct discord_s {
  struct discord_ws_s ws; //discord_t == (discord_t)(ws)
  struct discord_api_s api; //discord_t == (discord_t)(api-sizeof(ws))
  
  /* space for user-defined arbitrary data, libdiscord does not use
   *  this field.
   * can be set by discord_set_data() and retrieved by 
   *  discord_get_data() */
  void *data;

  struct _settings_s settings;
} discord_t;

/*for using Discord_api_request() as a template for every
 * kind of transfer*/
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

/* discord-api.c */

void Discord_api_init(struct discord_api_s *api, char token[]);
void Discord_api_cleanup(struct discord_api_s *api);

void Discord_api_load_message(void *p_message, char *str, size_t len);
void Discord_api_load_guild(void *p_guild, char *str, size_t len);
void Discord_api_load_user(void *p_user, char *str, size_t len);

void Discord_api_request(
  struct discord_api_s *api, 
  void *p_object, 
  discord_load_obj_cb *load_cb,
  char send_payload[], //only for POST/PUT methods
  enum http_method http_method,
  char endpoint[],
  ...);

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
