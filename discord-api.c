#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h> //for usleep
#include <stdarg.h>

#include <libdiscord.h>
#include "discord-common.h"

#define BASE_API_URL "https://discord.com/api"

/* initialize curl_slist's request header utility
 * @todo create distinction between bot and bearer token */
static struct curl_slist*
reqheader_init(char token[])
{
  char auth[MAX_HEADER_LEN];
  int ret = snprintf(auth, MAX_HEADER_LEN, "Authorization: Bot %s", token);
  ASSERT_S(ret < MAX_HEADER_LEN, "Out of bounds write attempt");

  struct curl_slist *new_header = NULL;
  void *tmp; //for checking potential allocation error

  new_header = curl_slist_append(new_header,"X-RateLimit-Precision: millisecond");
  ASSERT_S(NULL != new_header, "Out of memory");

  tmp = curl_slist_append(new_header, auth);
  ASSERT_S(NULL != tmp, "Out of memory");

  tmp = curl_slist_append(new_header,"User-Agent: libdiscord (http://github.com/cee-studio/libdiscord, v"LIBDISCORD_VERSION")");
  ASSERT_S(NULL != tmp, "Out of memory");

  tmp = curl_slist_append(new_header,"Content-Type: application/json");
  ASSERT_S(NULL != tmp, "Out of memory");

  tmp = curl_slist_append(new_header,"Accept: application/json");
  ASSERT_S(NULL != tmp, "Out of memory");

  return new_header;
}

/* a simple http header parser, splits key/field pairs at ':'
 * see: https://curl.se/libcurl/c/CURLOPT_HEADERFUNCTION.html */
static size_t
curl_resheader_cb(char *str, size_t size, size_t nmemb, void *p_userdata)
{
  size_t realsize = size * nmemb;
  struct api_header_s *pairs = p_userdata;

  char *ptr;
  if ( !(ptr = strchr(str, ':')) ) { //returns if can't find ':' token match
    return realsize;
  }

  *ptr = '\0'; //replace ':' with '\0' to separate key from field
  
  pairs->key[pairs->size] = str; //get the key part from string

  if ( !(ptr = strstr(ptr+1, "\r\n")) ) {//returns if can't find CRLF match
    return realsize;
  }

  *ptr = '\0'; //replace CRLF with '\0' to isolate key

  //adjust offset to start of field
  int offset = 1; //offset starts after '\0' separator token
  while (isspace(str[strlen(str) + offset])) {
    ++offset;
  }

  pairs->field[pairs->size] = &str[strlen(str) + offset]; //get the field part from string

  ++pairs->size; //update header amount of key/field pairs
  ASSERT_S(pairs->size < MAX_HEADER_SIZE, "Out of bounds write attempt");

  return realsize;
}

/* get api response body string
 * see: https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html */
static size_t
curl_resbody_cb(char *str, size_t size, size_t nmemb, void *p_userdata)
{
  size_t realsize = size * nmemb;
  struct api_resbody_s *body = p_userdata;

  //update response body string size
  char *tmp = realloc(body->str, body->size + realsize + 1);
  ASSERT_S(NULL != tmp, "Out of memory");

  body->str = tmp;
  memcpy(body->str + body->size, str, realsize);
  body->size += realsize;
  body->str[body->size] = '\0';

  return realsize;
}

/* initialize curl's easy handle with some default opt */
static CURL*
custom_easy_init(struct discord_api_s *api)
{
  CURL *new_ehandle = curl_easy_init();
  ASSERT_S(NULL != new_ehandle, "Out of memory");

  CURLcode ecode;
  /* DEBUG ONLY FUNCTIONS */
  //set debug callback
  D_ONLY(ecode = curl_easy_setopt(new_ehandle, CURLOPT_DEBUGFUNCTION, &Discord_utils_debug_cb));
  D_ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set ptr to settings containing dump files
  D_ONLY(ecode = curl_easy_setopt(new_ehandle, CURLOPT_DEBUGDATA, &api->p_client->settings));
  D_ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //enable verbose
  D_ONLY(ecode = curl_easy_setopt(new_ehandle, CURLOPT_VERBOSE, 1L));
  D_ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
  /* * * * * * * * * * * */

  //set ptr to request header we will be using for API communication
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_HTTPHEADER, api->req_header);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //enable follow redirections
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_FOLLOWLOCATION, 1L);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set response body callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_WRITEFUNCTION, &curl_resbody_cb);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set ptr to response body to be filled at callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_WRITEDATA, &api->body);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set response header callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_HEADERFUNCTION, &curl_resheader_cb);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set ptr to response header to be filled at callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_HEADERDATA, &api->pairs);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  return new_ehandle;
}

void
Discord_api_init(struct discord_api_s *api, char token[])
{
  api->req_header = reqheader_init(token);
  api->ehandle = custom_easy_init(api);
}

void
Discord_api_cleanup(struct discord_api_s *api)
{
  curl_slist_free_all(api->req_header);
  curl_easy_cleanup(api->ehandle); 

  if (api->body.str)
    free(api->body.str);
}

/* set specific http method used for the request */
static void
set_method(struct discord_api_s *api, enum http_method method, char postfields[])
{
  CURLcode ecode;
  switch (method) {
  case DELETE:
      ecode = curl_easy_setopt(api->ehandle, CURLOPT_CUSTOMREQUEST, "DELETE");
      ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
      break;
  case GET:
      ecode = curl_easy_setopt(api->ehandle, CURLOPT_HTTPGET, 1L);
      ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
      break;
  case POST:
      ecode = curl_easy_setopt(api->ehandle, CURLOPT_POST, 1L);
      ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
      //set ptr to payload that will be sent via POST/PUT
      ecode = curl_easy_setopt(api->ehandle, CURLOPT_POSTFIELDS, postfields);
      ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
      break;
  case PATCH:
      ecode = curl_easy_setopt(api->ehandle, CURLOPT_CUSTOMREQUEST, "PATCH");
      ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
      break;
  case PUT:
      ecode = curl_easy_setopt(api->ehandle, CURLOPT_UPLOAD, 1L);
      ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
      ecode = curl_easy_setopt(api->ehandle, CURLOPT_POSTFIELDS, postfields);
      ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
      break;
  default:
      ERROR("Unknown http method (code: %d)", method);
  }
}

/* set specific url used for request */
static void
set_url(struct discord_api_s *api, char endpoint[])
{
  char base_url[MAX_URL_LEN];
  int ret = snprintf(base_url, MAX_URL_LEN, BASE_API_URL"%s", endpoint);
  ASSERT_S(ret < MAX_URL_LEN, "Out of bounds write attempt");

  CURLcode ecode = curl_easy_setopt(api->ehandle, CURLOPT_URL, base_url);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
}

/* perform the request */
static void
perform_request(
  struct discord_api_s *api,
  void *p_object, 
  discord_load_obj_cb *load_cb)
{
  //try to perform the request and analyze output
  enum api_http_code http_code; //the http response code
  char *url = NULL; //the request URL
  CURLcode ecode;
  do {
    //perform the request
    ecode = curl_easy_perform(api->ehandle);
    ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

    //get response's http code
    ecode = curl_easy_getinfo(api->ehandle, CURLINFO_RESPONSE_CODE, &http_code);
    ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

    //get request's url
    ecode = curl_easy_getinfo(api->ehandle, CURLINFO_EFFECTIVE_URL, &url);
    ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

    D_PRINT("Request URL: %s", url);

    switch (http_code) {
    case HTTP_OK:
        if (load_cb) {
          (*load_cb)(p_object, api->body.str, api->body.size);
        }
    /* fall through */
    case HTTP_NO_CONTENT:
        break; /* DONE */
    case HTTP_TOO_MANY_REQUESTS:
    /* @todo dealing with ratelimits solely by checking for
     *  HTTP_TOO_MANY REQUESTS is not discord compliant */
     {
        char message[256];
        long long retry_after;

        json_scanf(api->body.str, api->body.size,
                    "[message]%s [retry_after]%lld",
                    message, &retry_after);

        D_PRINT("%s", message);

        usleep(retry_after*1000);

        break;
     }
    case CURL_NO_RESPONSE: //@todo implement circumvention
        ERROR("Curl couldn't fetch a HTTP response");
    default:
        ERROR("Unknown HTTP response code %d", http_code);
    }
    
    //reset the size of response body and header for a fresh start
    api->body.size = 0;
    api->pairs.size = 0;

  } while (http_code > 204);
}

/* template function for performing requests */
void
Discord_api_request(
  struct discord_api_s *api, 
  void *p_object, 
  discord_load_obj_cb *load_cb,
  char postfields[],
  enum http_method http_method,
  char endpoint[],
  ...)
{
  //create the url route
  va_list args;
  va_start (args, endpoint);

  char url_route[MAX_URL_LEN];
  int ret = vsnprintf(url_route, sizeof(url_route)-1, endpoint, args);
  ASSERT_S(ret < (int)sizeof(url_route)-1, "Out of bounds write of 'url_route'");

  va_end(args);

  //set the request method
  set_method(api, http_method, postfields);
  //set the request URL
  set_url(api, url_route);
  //perform the request
  perform_request(api, p_object, load_cb);
}
