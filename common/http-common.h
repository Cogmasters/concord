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
  HTTP_DELETE, HTTP_GET, HTTP_POST, HTTP_MIMEPOST, HTTP_PATCH, HTTP_PUT
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



#define MAX_HEADER_SIZE 100 + 1
#define MAX_HEADER_LEN  512 + 1
#define MAX_URL_LEN     512 + 1


// @todo rename to ua_header_s ?
struct api_header_s {
  char field[MAX_HEADER_SIZE][MAX_HEADER_LEN];
  char value[MAX_HEADER_SIZE][MAX_HEADER_LEN];
  int size;
};

// @todo rename to ua_settings_s ?
struct _settings_s { //@todo this whole struct is temporary
  char *token;
  FILE *f_json_dump;
  FILE *f_curl_dump;
};

//callback for object to be loaded by api response
typedef void (load_obj_cb)(char *str, size_t len, void *p_obj);

// @todo rename to ua_resp_handle_s ?
struct resp_handle {
  load_obj_cb *ok_cb;
  void *ok_obj; // the pointer to be passed to ok_cb

  load_obj_cb *err_cb;
  void *err_obj; // the pointer to be passed to err_cb
};

struct ua_conn_s {
  int is_available; // boolean

  CURL *ehandle; //the curl's easy handle used to perform requests
  struct sized_buffer resp_body; //the api response string
  struct api_header_s pairs; //the key/field pairs response header
  char *req_url;
  char *resp_url;
};

struct ua_handle_s {
  struct curl_slist *reqheader; //the request header sent to the api

  struct ua_conn_s *conns;
  size_t size;

  int num_available; // num of available conns

  struct _settings_s settings;
  char *base_url;

  void *data; // user arbitrary data for setopt_cb
  void (*setopt_cb)(CURL *ehandle, void *data); // set custom easy_setopts
};

typedef enum { 
  ACTION_SUCCESS, // continue after succesfull request
  ACTION_FAILURE, // continue after failed request
  ACTION_RETRY,   // retry connection
  ACTION_ABORT    // abort after failed request
} perform_action;

typedef perform_action (http_response_cb)(
    void *data,
    int httpcode, 
    struct ua_conn_s *conn);

// @todo rename to ua_perform_cbs ?
struct perform_cbs {
  void *p_data; // data to be received by callbacks

  void (*before_perform)(void*); // trigger before perform attempt

  http_response_cb *on_1xx; // triggers on 1xx code
  http_response_cb *on_2xx; // triggers on 2xx code
  http_response_cb *on_3xx; // triggers on 3xx code
  http_response_cb *on_4xx; // triggers on 4xx code
  http_response_cb *on_5xx; // triggers on 5xx code
};


char* http_code_print(int httpcode);
char* http_reason_print(int httpcode);
char* http_method_print(enum http_method method);

char* get_respheader_value(struct ua_conn_s *conn, char field[]);

void add_reqheader_pair(struct ua_handle_s *handle, char field[], char value[]);
void edit_reqheader_pair(struct ua_handle_s *handle, char field[], char new_value[]);
void del_reqheader_pair(struct ua_handle_s *handle, char field[]);

void ua_easy_setopt(struct ua_handle_s *handle, void *data, void (setopt_cb)(CURL *ehandle, void *data));
int ua_send_request(struct ua_conn_s *conn);
void ua_perform_request(
  struct ua_conn_s *conn, 
  struct resp_handle *resp_handle,
  struct perform_cbs *p_cbs);
struct ua_conn_s* ua_get_conn(struct ua_handle_s *handle);
void ua_set_method(struct ua_conn_s *conn, enum http_method method, struct sized_buffer *req_body);
void ua_set_url(struct ua_conn_s *conn, char base_api_url[], char endpoint[], va_list args);
void ua_conn_load(struct ua_handle_s *handle, struct ua_conn_s *conn);
void ua_handle_init(struct ua_handle_s *handle, char base_url[]);
void ua_handle_cleanup(struct ua_handle_s *handle);

void json_dump(const char *text, struct _settings_s *settings, const char *data);
int curl_debug_cb(CURL *ehandle, curl_infotype type, char *data, size_t size, void *p_userdata);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // HTTP_COMMON_H
