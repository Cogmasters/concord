#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h> //for usleep
#include <stdarg.h>

#include <libdiscord.h>
#include "discord-common.h"

#define BASE_API_URL "https://discord.com/api"

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
      ERROR("Invalid HTTP response code (code: %d)", code);
  }
}

/* initialize curl_slist's request header utility
 * @todo create distinction between bot and bearer token */
static struct curl_slist*
reqheader_init(char token[])
{
  char auth[MAX_HEADER_LEN];
  int ret = snprintf(auth, MAX_HEADER_LEN, "Authorization: Bot %s", token);
  ASSERT_S(ret < (int)sizeof(auth), "Out of bounds write attempt");

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

/* a simple http header parser, splits field/value pairs at ':'
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

  *ptr = '\0'; //replace ':' with '\0' to separate field from value
  
  pairs->field[pairs->size] = str; //get the field part from string

  if ( !(ptr = strstr(ptr+1, "\r\n")) ) {//returns if can't find CRLF match
    return realsize;
  }

  *ptr = '\0'; //replace CRLF with '\0' to isolate field

  //adjust offset to start of value
  int offset = 1; //offset starts after '\0' separator token
  while (isspace(str[strlen(str) + offset])) {
    ++offset;
  }

  pairs->value[pairs->size] = &str[strlen(str) + offset]; //get the value part from string

  ++pairs->size; //update header amount of field/value pairs
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
  ASSERT_S(ret < (int)sizeof(base_url), "Out of bounds write attempt");

  CURLcode ecode = curl_easy_setopt(api->ehandle, CURLOPT_URL, base_url);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
}

/* perform the request */
static void
perform_request(
  struct discord_api_s *api,
  void *p_object, 
  discord_load_obj_cb *load_cb,
  char bucket_route[])
{
  (void)bucket_route;

  //try to perform the request and analyze output
  bool retry;
  do {
    CURLcode ecode;
    //perform the request
    ecode = curl_easy_perform(api->ehandle);
    ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

    //get response's http code
    enum http_code code; //the http response code
    ecode = curl_easy_getinfo(api->ehandle, CURLINFO_RESPONSE_CODE, &code);
    ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

    //get request's url
    char *url = NULL; //the request URL
    ecode = curl_easy_getinfo(api->ehandle, CURLINFO_EFFECTIVE_URL, &url);
    ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

    D_PRINT("Request URL: %s", url);

    char *reason;
    switch (code) {
    case HTTP_OK:
        reason = "The request was completed succesfully.";
        retry = false;

        if (p_object && load_cb)
          (*load_cb)(p_object, api->body.str, api->body.size);

        break;
    case HTTP_CREATED:
        reason = "The entity was created succesfully.";
        retry = false;
        break;
    case HTTP_NO_CONTENT:
        reason = "The request completed succesfully but returned no content.";
        retry = false;
        break;
    case HTTP_NOT_MODIFIED:
        reason = "The entity was not modified (no action was taken).";
        retry = false;
        break;
    case HTTP_BAD_REQUEST:
        reason = "The request was improperly formatted, or the server couldn't understand it.";
        retry = false;
        break;
    case HTTP_UNAUTHORIZED:
        reason = "The Authorization header was missing or invalid.";
        retry = false;
        break;
    case HTTP_FORBIDDEN:
        reason = "The Authorization token you passed did not have permission to the resource.";
        retry = false;
        break;
    case HTTP_NOT_FOUND:
        reason = "The resource at the location specified doesn't exist.";
        retry = false;
        break;
    case HTTP_METHOD_NOT_ALLOWED:
        reason = "The HTTP method used is not valid for the location specified.";
        retry = false;
        break;
    case HTTP_TOO_MANY_REQUESTS:
        reason = "You got ratelimited.";
        retry = true;
    /* @todo dealing with ratelimits solely by checking for
     *  HTTP_TOO_MANY REQUESTS is not discord compliant */
     {
        char message[256];
        long long retry_after;

        json_scanf(api->body.str, api->body.size,
                    "[message]%s [retry_after]%lld",
                    message, &retry_after);

        D_NOTOP_PRINT("Ratelimit Message: %s", message);

        usleep(retry_after*1000);

        break;
     }
    case HTTP_GATEWAY_UNAVAILABLE:
        reason = "There was not a gateway available to process your request. Wait a bit and retry.";
        retry = true;

        usleep(5000); //wait a bit
        break;
    case CURL_NO_RESPONSE:
        reason = "Curl couldn't fetch a HTTP response.";
        retry = true;
        break;
    default:
        if (code >= 500) {
          reason = "The server had an error processing your request.";
          retry = true;
        }
        else {
          reason = "Unknown HTTP method.";
          retry = false;
        }

        break;
    }

    if (true == retry || code < 400) {
      D_NOTOP_PRINT("(%d)%s - %s", code, http_code_print(code), reason);

      /* WORK IN PROGRESS, THE FOLLOWING SHOULD BE IGNORED FOR REVIEW *

      int remaining = Discord_ratelimit_remaining(&api->pairs);
      long long delay_ms = Discord_ratelimit_delay(remaining, &api->pairs, true);
      char *bucket_hash = Discord_ratelimit_bucket(&api->pairs);

      (void)remaining;
      (void)delay_ms;
      (void)bucket_hash;

      * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    }
    else {
      ERROR("(%d)%s - %s", code, http_code_print(code), reason);
    }

    //reset the size of response body and header pairs for a fresh start
    api->body.size = 0;
    api->pairs.size = 0;

  } while (true == retry);
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
  int ret = vsnprintf(url_route, sizeof(url_route), endpoint, args);
  ASSERT_S(ret < (int)sizeof(url_route), "Out of bounds write attempt");

  va_end(args);

  set_method(api, http_method, postfields); //set the request method
  set_url(api, url_route); //set the request URL

  //route that we will attempt to match a bucket with
  char *route = Discord_ratelimit_route(endpoint);
  perform_request(api, p_object, load_cb, route); //perform the request
}
