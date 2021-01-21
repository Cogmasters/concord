#ifndef HTTP_COMMON_H_
#define HTTP_COMMON_H_
#include <curl/curl.h>

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

struct _settings_s { //@todo this whole struct is temporary
  char *token;
  FILE *f_json_dump;
  FILE *f_curl_dump;
};


//callback for object to be loaded by api response
typedef void (load_obj_cb)(void *p_obj, char *str, size_t len);


static void
sleep_ms(const long long delay_ms)
{
  const struct timespec t = {
          .tv_sec = delay_ms / 1000,
          .tv_nsec = (delay_ms % 1000) * 1e6
  };

  nanosleep(&t, NULL);
}

static char*
http_code_print(enum http_code code)
{
  switch (code) {
    CASE_RETURN_STR(HTTP_OK);
    CASE_RETURN_STR(HTTP_CREATED);
    CASE_RETURN_STR(HTTP_NO_CONTENT);
    CASE_RETURN_STR(HTTP_NOT_MODIFIED);
    CASE_RETURN_STR(HTTP_BAD_REQUEST);
    CASE_RETURN_STR(HTTP_UNAUTHORIZED);
    CASE_RETURN_STR(HTTP_FORBIDDEN);
    CASE_RETURN_STR(HTTP_NOT_FOUND);
    CASE_RETURN_STR(HTTP_METHOD_NOT_ALLOWED);
    CASE_RETURN_STR(HTTP_TOO_MANY_REQUESTS);
    CASE_RETURN_STR(HTTP_GATEWAY_UNAVAILABLE);
    default:
      if (code >= 500) {
        return "5xx SERVER ERROR";
      }
      ERROR("Invalid HTTP response code (code: %d)", code);
  }
}

/* set specific http method used for the request */
static void
set_method(CURL *ehandle, enum http_method method, char postfields[])
{
  CURLcode ecode;
  switch (method) {
    case DELETE:
      ecode = curl_easy_setopt(ehandle, CURLOPT_CUSTOMREQUEST, "DELETE");
      ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
      break;
    case GET:
      ecode = curl_easy_setopt(ehandle, CURLOPT_HTTPGET, 1L);
      ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
      break;
    case POST:
      ecode = curl_easy_setopt(ehandle, CURLOPT_POST, 1L);
      ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
      //set ptr to payload that will be sent via POST/PUT
      ecode = curl_easy_setopt(ehandle, CURLOPT_POSTFIELDS, postfields);
      ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
      break;
    case PATCH:
      ecode = curl_easy_setopt(ehandle, CURLOPT_CUSTOMREQUEST, "PATCH");
      ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
      break;
    case PUT:
      ecode = curl_easy_setopt(ehandle, CURLOPT_UPLOAD, 1L);
      ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
      ecode = curl_easy_setopt(ehandle, CURLOPT_POSTFIELDS, postfields);
      ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
      break;
    default:
      ERROR("Unknown http method (code: %d)", method);
  }
}

#endif