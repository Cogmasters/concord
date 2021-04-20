#ifndef USER_AGENT_H
#define USER_AGENT_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdint.h> /* uint64_t */
#include <curl/curl.h> 
#include "ntl.h" /* struct sized_buffer */
#include "logconf.h"

/* FORWARD DECLARATIONS */
struct user_agent; // the user agent that perform requests
struct ua_conn;    // unique connector per request

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

#define UA_MAX_HEADER_SIZE 100 + 1
#define UA_MAX_HEADER_LEN  1024 + 1
#define UA_MAX_URL_LEN     512 + 1

typedef enum { 
  UA_SUCCESS = 1,  // continue after succesfull request
  UA_FAILURE,      // continue after failed request
  UA_RETRY,        // retry connection
  UA_ABORT         // abort after failed request
} ua_status_t;

struct sized_buffer ua_conn_get_resp_body(struct ua_conn *conn);
ua_status_t ua_conn_get_status(struct ua_conn *conn);
uint64_t ua_conn_timestamp(struct ua_conn *conn);

//callback for object to be loaded by api response
typedef void (load_obj_cb)(char *str, size_t len, void *p_obj);
typedef void (cxt_load_obj_cb)(void * cxt, char *str, size_t len, void *p_obj);

struct ua_resp_handle {
  void *cxt; // the context for cxt_ok_cb;

  load_obj_cb *ok_cb;
  void *ok_obj; // the pointer to be passed to ok_cb

  load_obj_cb *err_cb;
  void *err_obj; // the pointer to be passed to err_cb

  cxt_load_obj_cb *cxt_ok_cb; // ok call back with an execution context
  cxt_load_obj_cb *cxt_err_cb; // err call back with an execution context
};

typedef ua_status_t 
(http_response_cb)(void *data, int httpcode, struct ua_conn *conn);

/* these can be used on any MT contexts, but the user still
    have to synchronize his data accessed between callbacks */
struct ua_callbacks {
  void *data; // user arbitrary data to be passed to callbacks

  int (*on_startup)(void *data); // exec before loop starts (return 1 for proceed, 0 for abort)
  void (*on_iter_start)(void *data); // execs at end of every loop iteration
  void (*on_iter_end)(void *data, struct ua_conn *conn); // execs at end of every loop iteration

  http_response_cb *on_1xx; // execs on 1xx code
  http_response_cb *on_2xx; // execs on 2xx code
  http_response_cb *on_3xx; // execs on 3xx code
  http_response_cb *on_4xx; // execs on 4xx code
  http_response_cb *on_5xx; // execs on 5xx code
};

char* http_code_print(int httpcode);
char* http_reason_print(int httpcode);
char* http_method_print(enum http_method method);

char* ua_respheader_value(struct ua_conn *conn, char field[]);

void ua_reqheader_add(struct user_agent *ua, char field[], char value[]);
void ua_reqheader_del(struct user_agent *ua, char field[]);

void ua_easy_setopt(struct user_agent *ua, void *data, void (setopt_cb)(CURL *ehandle, void *data));
void ua_mime_setopt(struct user_agent *ua, void *data, curl_mime* (mime_cb)(CURL *ehandle, void *data)); // @todo this is temporary

struct user_agent* ua_init(const char base_url[], struct logconf *conf);
void ua_cleanup(struct user_agent *ua);

char* ua_get_url(struct user_agent *ua);
void ua_set_url(struct user_agent *ua, const char base_url[]);
void ua_block_ms(struct user_agent *ua, const uint64_t wait_ms);
void ua_vrun(
  struct user_agent *ua,
  struct ua_resp_handle *resp_handle,
  struct sized_buffer *req_body,
  struct ua_callbacks *cbs,
  enum http_method http_method, char endpoint[], va_list args);
void ua_run(
  struct user_agent *ua,
  struct ua_resp_handle *resp_handle,
  struct sized_buffer *req_body,
  struct ua_callbacks *cbs,
  enum http_method http_method, char endpoint[], ...);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // USER_AGENT_H
