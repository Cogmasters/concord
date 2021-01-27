#ifndef HTTP_COMMON_H
#define HTTP_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <curl/curl.h>
#include "orka-debug.h"

/* UTILITY MACROS */
#define STREQ(str1, str2) (0 == strcmp(str1, str2))
#define STRNEQ(str1, str2, n) (0 == strncmp(str1, str2, n))
//check if string is empty
#define IS_EMPTY_STRING(str) (!(str) || !*(str))
//if case matches return token as string
#define CASE_RETURN_STR(opcode) case opcode: return #opcode

//possible http methods
enum http_method {
  HTTP_DELETE, HTTP_GET, HTTP_POST, HTTP_PATCH, HTTP_PUT
};


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
  HTTP_UNPROCESSABLE_ENTITY     = 422,
  HTTP_TOO_MANY_REQUESTS        = 429,
  HTTP_GATEWAY_UNAVAILABLE      = 502,

  CURL_NO_RESPONSE              = 0,
};


struct api_resbody_s {
  char *str; //the request/response str
  size_t size; //the request/response str length
};

#define MAX_HEADER_SIZE 100
#define MAX_URL_LEN     512
#define MAX_HEADER_LEN  512

struct api_header_s {
  char field[MAX_HEADER_SIZE][MAX_HEADER_LEN];
  char value[MAX_HEADER_SIZE][MAX_HEADER_LEN];
  int size;
};

struct _settings_s { //@todo this whole struct is temporary
  char *token;
  FILE *f_json_dump;
  FILE *f_curl_dump;
};

//callback for object to be loaded by api response
typedef void (load_obj_cb)(char *str, size_t len, void *p_obj);

// response handle
struct resp_handle {
  load_obj_cb *ok_cb;
  void *ok_obj; // the pointer to be passed to ok_cb

  load_obj_cb *err_cb;
  void *err_obj;
};

void sleep_ms(const long long delay_ms);
long long timestamp_ms();
void timestamp_str(char str[], int len);

char* get_header_value(struct api_header_s *pairs, char header_field[]);
char* http_code_print(enum http_code code);
char* http_method_print(enum http_method method);

/* set specific http method used for the request */
void set_method(CURL *ehandle, enum http_method method, struct api_resbody_s *body);
/* set url to be used for the request */
void set_url(CURL *ehandle, char *base_api_url, char endpoint[]);

CURL* custom_easy_init(struct _settings_s *settings,
                 struct curl_slist *req_header,
                 struct api_header_s *pairs,
                 struct api_resbody_s *body);

void json_dump(const char *text, struct _settings_s *settings, const char *data);
int curl_debug_cb(CURL *ehandle, curl_infotype type, char *data, size_t size, void *p_userdata);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // HTTP_COMMON_H
