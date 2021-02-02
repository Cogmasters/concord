#ifndef HTTP_COMMON_H
#define HTTP_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <curl/curl.h>
#include "orka-debug.h"
#include "ntl.h"

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


/* COMMON HTTP RESPONSE CODES
https://en.wikipedia.org/wiki/List_of_HTTP_status_codes */
#define CURL_NO_RESPONSE           0
#define HTTP_OK                   200
#define HTTP_CREATED              201
#define HTTP_NO_CONTENT           204
#define HTTP_NOT_MODIFIED         304
#define HTTP_BAD_REQUEST          400
#define HTTP_UNAUTHORIZED         401
#define HTTP_FORBIDDEN            403
#define HTTP_NOT_FOUND            404
#define HTTP_METHOD_NOT_ALLOWED   405
#define HTTP_UNPROCESSABLE_ENTITY 422
#define HTTP_TOO_MANY_REQUESTS    429
#define HTTP_GATEWAY_UNAVAILABLE  502


#define MAX_HEADER_SIZE 100
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
  void *err_obj; // the pointer to be passed to err_cb
};

char* get_header_value(struct api_header_s *pairs, char header_field[]);
char* http_code_print(int httpcode);
char* http_reason_print(int httpcode);
char* http_method_print(enum http_method method);

/* set url to be used for the request */
void set_url(CURL *ehandle, char base_api_url[], char endpoint[], va_list args);
/* set specific http method used for the request */
void set_method(CURL *ehandle, enum http_method method, struct sized_buffer *request_body);

typedef enum { ACTION_DONE, ACTION_RETRY, ACTION_ABORT } perform_action;

typedef perform_action (http_response_cb)(
    void *data,
    int httpcode, 
    struct sized_buffer *request_body,
    struct api_header_s *pairs);

struct perform_cbs {
  void *p_data; // data to be received by callbacks

  void (*before_perform)(void*); // trigger before perform attempt

  http_response_cb *on_1xx; // triggers on 1xx code
  http_response_cb *on_2xx; // triggers on 2xx code
  http_response_cb *on_3xx; // triggers on 3xx code
  http_response_cb *on_4xx; // triggers on 4xx code
  http_response_cb *on_5xx; // triggers on 5xx code
};

void perform_request(
  struct resp_handle *resp_handle,
  struct sized_buffer *request_body,
  struct api_header_s *pairs,
  CURL *ehandle,
  struct perform_cbs *cbs);

CURL* custom_easy_init(struct _settings_s *settings,
                 struct curl_slist *req_header,
                 struct api_header_s *pairs,
                 struct sized_buffer *response_body);

void json_dump(const char *text, struct _settings_s *settings, const char *data);
int curl_debug_cb(CURL *ehandle, curl_infotype type, char *data, size_t size, void *p_userdata);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // HTTP_COMMON_H
