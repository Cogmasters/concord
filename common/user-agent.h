#ifndef USER_AGENT_H
#define USER_AGENT_H

#include <inttypes.h>
#include <curl/curl.h>
#include <pthread.h>

#include "orka-config.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//possible http methods
enum http_method {
  HTTP_DELETE, 
  HTTP_GET, 
  HTTP_POST, 
  HTTP_MIMEPOST, 
  HTTP_PATCH, 
  HTTP_PUT
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
#define MAX_HEADER_LEN  1024 + 1
#define MAX_URL_LEN     512 + 1


struct ua_respheader_s {
  char field[MAX_HEADER_SIZE][MAX_HEADER_LEN];
  char value[MAX_HEADER_SIZE][MAX_HEADER_LEN];
  int size;
};

typedef enum { 
  UA_IDLE = 0, // haven't performed yet
  UA_SUCCESS,  // continue after succesfull request
  UA_FAILURE,  // continue after failed request
  UA_RETRY,    // retry connection
  UA_ABORT     // abort after failed request
} ua_status_t;

struct ua_conn_s {
  bool is_busy;
  uint64_t perform_tstamp; // timestamp of when the request completed

  CURL *ehandle; //the curl's easy handle used to perform requests
  struct sized_buffer resp_body; //the api response string
  struct ua_respheader_s resp_header; //the key/field response header

  char req_url[MAX_URL_LEN]; //request's url
  char *resp_url; //response's url

  ua_status_t status; //the conn request's status

  void *data; //user arbitrary data
};

void* ua_conn_set_data(struct ua_conn_s *conn, void *data);
void* ua_conn_get_data(struct ua_conn_s *conn);

//callback for object to be loaded by api response
typedef void (load_obj_cb)(char *str, size_t len, void *p_obj);

typedef void (cxt_load_obj_cb)(void * cxt, char *str, size_t len, void *p_obj);

struct resp_handle {
  void *cxt; // the context for cxt_ok_cb;

  load_obj_cb *ok_cb;
  void *ok_obj; // the pointer to be passed to ok_cb

  load_obj_cb *err_cb;
  void *err_obj; // the pointer to be passed to err_cb

  // ok call back with an execution context
  cxt_load_obj_cb *cxt_ok_cb;

  // err call back with an execution context
  cxt_load_obj_cb *cxt_err_cb;
};

struct user_agent_s {
  struct orka_config config;
  struct curl_slist *req_header; // the request header sent to the api

  struct ua_conn_s **conn_pool; // connection pool for reuse
  int num_notbusy; // num of available conns
  size_t num_conn; // amount of conns created

  char *base_url;

  uint64_t blockuntil_tstamp; // for global ratelimiting purposes
  pthread_mutex_t lock;

  void *data; // user arbitrary data for setopt_cb
  void (*setopt_cb)(CURL *ehandle, void *data); // set custom easy_setopts

  void *data2; // @todo this is temporary
  curl_mime *mime; // @todo this is temporary
  curl_mime* (*mime_cb)(CURL *ehandle, void *data); // @todo this is temporary
};

typedef ua_status_t 
(http_response_cb)(void *data, int httpcode, struct ua_conn_s *conn);

/* these can be used on any MT contexts, but the user still
    have to synchronize his data accessed between callbacks */
struct ua_callbacks {
  void *data; // user arbitrary data to be passed to callbacks

  int (*on_startup)(void *data); // exec before loop starts (return 1 for proceed, 0 for abort)
  void (*on_iter_start)(void *data); // execs at end of every loop iteration
  void (*on_iter_end)(void *data, struct ua_conn_s *conn); // execs at end of every loop iteration

  http_response_cb *on_1xx; // execs on 1xx code
  http_response_cb *on_2xx; // execs on 2xx code
  http_response_cb *on_3xx; // execs on 3xx code
  http_response_cb *on_4xx; // execs on 4xx code
  http_response_cb *on_5xx; // execs on 5xx code
};

char* http_code_print(int httpcode);
char* http_reason_print(int httpcode);
char* http_method_print(enum http_method method);

char* ua_respheader_value(struct ua_conn_s *conn, char field[]);

void ua_reqheader_add(struct user_agent_s *ua, char field[], char value[]);
void ua_reqheader_del(struct user_agent_s *ua, char field[]);

void ua_easy_setopt(struct user_agent_s *ua, void *data, void (setopt_cb)(CURL *ehandle, void *data));
void ua_mime_setopt(struct user_agent_s *ua, void *data, curl_mime* (mime_cb)(CURL *ehandle, void *data)); // @todo this is temporary

void ua_init(struct user_agent_s *ua, const char base_url[]);
void ua_config_init(
  struct user_agent_s *ua, 
  const char base_url[], 
  const char tag[], 
  const char config_file[]);
void ua_cleanup(struct user_agent_s *ua);
void ua_block_ms(struct user_agent_s *ua, const uint64_t wait_ms);
void ua_vrun(
  struct user_agent_s *ua,
  struct resp_handle *resp_handle,
  struct sized_buffer *req_body,
  struct ua_callbacks *cbs,
  enum http_method http_method,
  char endpoint[], va_list args);
void ua_run(
  struct user_agent_s *ua,
  struct resp_handle *resp_handle,
  struct sized_buffer *req_body,
  struct ua_callbacks *cbs,
  enum http_method http_method,
  char endpoint[], ...);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // USER_AGENT_H
