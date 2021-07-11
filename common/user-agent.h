#ifndef USER_AGENT_H
#define USER_AGENT_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdint.h> /* uint64_t */
#include <curl/curl.h> 
#include "ntl.h" /* struct sized_buffer */
#include "types.h"
#include "logconf.h"

/* FORWARD DECLARATIONS */
struct user_agent; // the user agent that perform requests

//possible http methods
enum http_method {
  HTTP_INVALID = -1,
  HTTP_DELETE, 
  HTTP_GET, 
  HTTP_POST, 
  HTTP_MIMEPOST, 
  HTTP_PATCH, 
  HTTP_PUT
};

/* COMMON HTTP RESPONSE CODES
https://en.wikipedia.org/wiki/List_of_HTTP_status_codes */
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
#define UA_MAX_URL_LEN     512 + 1

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

struct ua_resp_header {
  /**
   * the api response header and its length
   */
  char *buf;
  size_t length;
  /**
   * the real size occupied in memory by 'buf'
   */
  size_t bufsize;

  /**
   * index and size of individual field and values
   *        from 'buf'
   */
  struct {
    struct {
      uintptr_t idx;
      size_t size;
    } field, value;
  } pairs[UA_MAX_HEADER_SIZE];
  /**
   * amount of field/value pairs
   */
  int size;
};

struct ua_resp_body {
  /**
   * the api response string and its length
   */
  char *buf;
  size_t length;
  /**
   * the real size occupied in memory by 'buf'
   */
  size_t bufsize;
};

struct ua_info {
  struct loginfo loginfo;
  /**
   * how the request went 
   *    equal 0 means success (2xx)
   *    greater than 0 means failure (check value for http code)
   *    lesser than 0 means failure from specialized error codes
   */
  ORCAcode code;
  /** 
   * request's url
   */
  char req_url[UA_MAX_URL_LEN];
  /** 
   * timestamp of when its request completed
   */
  uint64_t req_tstamp;
  /**
   * the key/field response header
   */
  struct ua_resp_header resp_header;
  /**
   * the response body
   */
  struct ua_resp_body resp_body;
};

char* http_code_print(int httpcode);
char* http_reason_print(int httpcode);
char* http_method_print(enum http_method method);
enum http_method http_method_eval(char method[]);

void ua_reqheader_add(struct user_agent *ua, const char field[], const char value[]);
void ua_reqheader_del(struct user_agent *ua, const char field[]);
char* ua_reqheader_str(struct user_agent *ua, char *buf, size_t bufsize);

void ua_easy_setopt(struct user_agent *ua, void *data, void (setopt_cb)(CURL *ehandle, void *data));
void ua_mime_setopt(struct user_agent *ua, void *data, curl_mime* (mime_cb)(CURL *ehandle, void *data)); // @todo this is temporary

struct user_agent* ua_init(struct logconf *conf);
void ua_cleanup(struct user_agent *ua);

void ua_set_url(struct user_agent *ua, const char base_url[]);
char* ua_get_url(struct user_agent *ua);
void ua_block_ms(struct user_agent *ua, const uint64_t wait_ms);
ORCAcode ua_vrun(
  struct user_agent *ua,
  struct ua_info *info,
  struct ua_resp_handle *resp_handle,
  struct sized_buffer *req_body,
  enum http_method http_method, char endpoint[], va_list args);
ORCAcode ua_run(
  struct user_agent *ua,
  struct ua_info *info,
  struct ua_resp_handle *resp_handle,
  struct sized_buffer *req_body,
  enum http_method http_method, char endpoint[], ...);

void ua_info_cleanup(struct ua_info *info);
struct sized_buffer ua_info_respheader_field(struct ua_info *info, char field[]);
struct sized_buffer ua_info_get_resp_body(struct ua_info *info);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // USER_AGENT_H
