#ifndef LIBDISCORD_COMMON_H_
#define LIBDISCORD_COMMON_H_

//#include <libdiscord.h> (implicit)

#include <curl/curl.h>
#include <libjscon.h>

#include "discord-tool-debug.h"

#define BASE_API_URL "https://discord.com/api"
#define BASE_GATEWAY_URL "wss://gateway.discord.gg/?v=6&encoding=json"

struct api_response_s {
  char *str; //the response str
  size_t size; //the response str length
};

#define MAX_HEADER_SIZE 25

struct api_header_s {
  char *key[MAX_HEADER_SIZE];
  char *field[MAX_HEADER_SIZE];
  int size;
};

struct discord_api_s {
  CURL *easy_handle; //the curl's easy handle used to perform requests
  struct curl_slist *req_header; //the request header sent to the api
  struct api_response_s res_body; //the api response string
  struct api_header_s res_pairs; //the key/field pairs response header
};

typedef struct discord_s {
  struct discord_api_s api;
} discord_t;

typedef void (discord_load_obj_ft)(void **p_object, struct api_response_s *res_body);

enum http_method {
  NONE,
  DELETE,
  GET,
  POST,
  PATCH,
  PUT,
};

enum discord_limits {
  MAX_NAME_LEN           = 100,
  MAX_TOPIC_LEN          = 1024,
  MAX_DESCRIPTION_LEN    = 1024,
  MAX_USERNAME_LEN       = 32,
  MAX_DISCRIMINATOR_LEN  = 5,
  MAX_HASH_LEN           = 1024,
  MAX_LOCALE_LEN         = 15,
  MAX_EMAIL_LEN          = 254,
  MAX_REGION_LEN         = 15,
  MAX_HEADER_LEN         = 512,
  MAX_URL_LEN            = 512,
};

/* HTTP RESPONSE CODES
https://discord.com/developers/docs/topics/opcodes-and-status-codes#http-http-response-codes */
enum discord_http_code {
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

/* SNOWFLAKES
https://discord.com/developers/docs/reference#snowflakes */
enum discord_snowflake {
  SNOWFLAKE_INCREMENT           = 12,
  SNOWFLAKE_PROCESS_ID          = 17,
  SNOWFLAKE_INTERNAL_WORKER_ID  = 22,
  SNOWFLAKE_TIMESTAMP           = 64,
};

/* ENDPOINTS */
#define CHANNELS           "/channels/%s"
#define CHANNELS_MESSAGES  CHANNELS"/messages"

#define GUILDS             "/guilds/%s"
#define GUILDS_CHANNELS    GUILDS"/channels"

#define USERS              "/users/%s"
#define USERS_GUILDS       USERS"/guilds"

/* discord-api.c */

void Discord_api_init(struct discord_api_s *api, char token[]);
void Discord_api_cleanup(struct discord_api_s *api);

void Discord_api_request(
  struct discord_api_s *api, 
  void **p_object, 
  discord_load_obj_ft *load_cb,
  enum http_method http_method,
  char endpoint[],
  ...);

#endif
