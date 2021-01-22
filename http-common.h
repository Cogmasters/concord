#ifndef HTTP_COMMON_H_
#define HTTP_COMMON_H_
#include <curl/curl.h>

/* UTILITY MACROS */
//#define STREQ(str1, str2) (0 == strcmp(str1, str2))
//#define STRNEQ(str1, str2, n) (0 == strncmp(str1, str2, n))
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
typedef void (load_obj_cb)(void *p_obj, char *str, size_t len);
typedef void (curl_debug_cb)(
        CURL *ehandle,
        curl_infotype type,
        char *data,
        size_t size,
        void *p_userdata);

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
  return NULL;
}

/* set specific http method used for the request */
static void
set_method(CURL *ehandle, enum http_method method, struct api_resbody_s * body)
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
      //curl_easy_setopt(ehandle, CURLOPT_POST, 1L);
      //set ptr to payload that will be sent via POST/PUT
      curl_easy_setopt(ehandle, CURLOPT_POSTFIELDS, body->str);
      curl_easy_setopt(ehandle, CURLOPT_POSTFIELDSIZE, body->size);
      break;
    case PATCH:
      curl_easy_setopt(ehandle, CURLOPT_CUSTOMREQUEST, "PATCH");
      break;
    case PUT:
      curl_easy_setopt(ehandle, CURLOPT_UPLOAD, 1L);
      curl_easy_setopt(ehandle, CURLOPT_POSTFIELDS, body->str);
      curl_easy_setopt(ehandle, CURLOPT_POSTFIELDSIZE, body->size);
      break;
    default:
      ERROR("Unknown http method (code: %d)", method);
  }
}

static void
set_url(CURL * ehandle, char * base_api_url, char endpoint[])
{
  char base_url[MAX_URL_LEN];
  int ret = snprintf(base_url, sizeof(base_url), "%s%s", base_api_url, endpoint);
  ASSERT_S(ret < (int)sizeof(base_url), "Out of bounds write attempt");

  CURLcode ecode = curl_easy_setopt(ehandle, CURLOPT_URL, base_url);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
}

static size_t
curl_resheader_cb(char *str, size_t size, size_t nmemb, void *p_userdata)
{
  size_t realsize = size * nmemb;
  struct api_header_s *pairs = (struct api_header_s *)p_userdata;

  char *ptr;
  if (!(ptr = strchr(str, ':'))) { //returns if can't find ':' token match
    return realsize;
  }

  *ptr = '\0'; //replace ':' with '\0' to separate field from value

  int ret = snprintf(pairs->field[pairs->size], MAX_HEADER_LEN, "%s", str);
  ASSERT_S(ret < MAX_HEADER_LEN, "oob of paris->field");

  if (!(ptr = strstr(ptr + 1, "\r\n"))) {//returns if can't find CRLF match
    return realsize;
  }

  *ptr = '\0'; //replace CRLF with '\0' to isolate field

  //adjust offset to start of value
  int offset = 1; //offset starts after '\0' separator token
  while (isspace(str[strlen(str) + offset])) {
    ++offset;
  }

  //get the value part from string
  ret = snprintf(pairs->value[pairs->size], MAX_HEADER_LEN, "%s",
                 &str[strlen(str) + offset]);
  ASSERT_S(ret < MAX_HEADER_LEN, "oob write attempt");

  ++pairs->size; //update header amount of field/value pairs
  ASSERT_S(pairs->size < MAX_HEADER_SIZE, "oob write of pairs");

  return realsize;
}

/* get api response body string
* see: https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html */
static size_t
curl_resbody_cb(char *str, size_t size, size_t nmemb, void *p_userdata)
{
  size_t realsize = size * nmemb;
  struct api_resbody_s *body = (struct api_resbody_s *)p_userdata;

  //update response body string size
  char *tmp = (char *)realloc(body->str, body->size + realsize + 1);
  body->str = tmp;
  memcpy(body->str + body->size, str, realsize);
  body->size += realsize;
  body->str[body->size] = '\0';

  fprintf (stderr, "%s\n", body->str);
  return realsize;
}

static CURL*
custom_easy_init(struct _settings_s * settings,
                 curl_debug_cb debug_cb,
                 struct curl_slist * req_header,
                 struct api_header_s * pairs,
                 struct api_resbody_s * body)
{
  CURL *new_ehandle = curl_easy_init();

  CURLcode ecode;
  /* DEBUG ONLY FUNCTIONS */
  //set debug callback
  D_ONLY(ecode = curl_easy_setopt(new_ehandle, CURLOPT_DEBUGFUNCTION, debug_cb));
  D_ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set ptr to settings containing dump files
  D_ONLY(ecode = curl_easy_setopt(new_ehandle, CURLOPT_DEBUGDATA, settings));
  D_ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //enable verbose
  D_ONLY(ecode = curl_easy_setopt(new_ehandle, CURLOPT_VERBOSE, 1L));
  D_ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
  /* * * * * * * * * * * */

  //set ptr to request header we will be using for API communication
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_HTTPHEADER, req_header);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //enable follow redirections
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_FOLLOWLOCATION, 1L);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set response body callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_WRITEFUNCTION,
                           &curl_resbody_cb);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set ptr to response body to be filled at callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_WRITEDATA, body);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set response header callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_HEADERFUNCTION,
                           &curl_resheader_cb);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set ptr to response header to be filled at callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_HEADERDATA, pairs);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  return new_ehandle;
}
#endif