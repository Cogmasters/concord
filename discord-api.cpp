#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h> //for usleep
#include <stdarg.h>
#include "http-common.h"

#define BASE_API_URL "https://discord.com/api"

namespace discord {
namespace v8 {
namespace api {

struct data {
  struct curl_slist *req_header; //the request header sent to the api

  struct api_resp_body_s body; //the api response string
  struct api_header_pairs pairs; //the key/field pairs response header
  CURL *ehandle; //the curl's easy handle used to perform requests

  struct _settings_s settings;
};

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

  tmp = curl_slist_append(new_header,"Accept: application/json");
  ASSERT_S(NULL != tmp, "Out of memory");

  tmp = curl_slist_append(new_header, auth);
  ASSERT_S(NULL != tmp, "Out of memory");

  tmp = curl_slist_append(new_header,"User-Agent: orca (http://github.com/cee-studio/orca, v"LIBDISCORD_VERSION")");
  ASSERT_S(NULL != tmp, "Out of memory");

  tmp = curl_slist_append(new_header,"Content-Type: application/json");
  ASSERT_S(NULL != tmp, "Out of memory");

  return new_header;
}

void
init(struct data *api, char username[], char token[])
{
  api->req_header = reqheader_init();
  api->ehandle = custom_easy_init(api);
}

void
cleanup(struct data *api)
{
  curl_slist_free_all(api->req_header);
  curl_easy_cleanup(api->ehandle);

  if (api->body.str) {
    free(api->body.str);
  }
}

/* perform the request */
static void
perform_request(
  struct data *api,
  void *p_object, 
  load_obj_cb *load_cb,
  char endpoint[])
{
  enum { //possible actions taken after a http response code
    DONE, RETRY, ABORT
  } action;

  //attempt to fetch a bucket handling connections from this endpoint
  struct bucket *bucket = Discord_ratelimit_tryget_bucket(api, endpoint);
  do {
    if (bucket) { //bucket exists, we will check for pending delays
      long long delay_ms = Discord_ratelimit_delay(bucket, true);
      D_PRINT("RATELIMITING (reach bucket's connection threshold):\n\t"
              "\tEndpoint:\t%s\n\t"
              "\tBucket:\t\t%s\n\t"
              "\tWait for:\t%lld ms",
              endpoint, bucket->hash, delay_ms);

      sleep_ms(delay_ms); //sleep for delay amount (if any)
    }


    CURLcode ecode;
    //perform the connection
    ecode = curl_easy_perform(api->ehandle);
    ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

    //get response's code
    const enum http_code code;
    ecode = curl_easy_getinfo(api->ehandle, CURLINFO_RESPONSE_CODE, &code);
    ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

    //get request's url
    const char *url = NULL;
    ecode = curl_easy_getinfo(api->ehandle, CURLINFO_EFFECTIVE_URL, &url);
    ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

    D_PRINT("Request URL: %s", url);


    const char *reason; //verbose reason of http code
    switch (code) {
    case HTTP_OK:
        reason = "The request was completed succesfully.";
        action = DONE;

        if (p_object && load_cb) {
          (*load_cb)(p_object, api->body.str, api->body.size);
        }

        break;
    case HTTP_CREATED:
        reason = "The entity was created succesfully.";
        action = DONE;
        break;
    case HTTP_NO_CONTENT:
        reason = "The request completed succesfully but returned no content.";
        action = DONE;
        break;
    case HTTP_NOT_MODIFIED:
        reason = "The entity was not modified (no action was taken).";
        action = DONE;
        break;
    case HTTP_BAD_REQUEST:
        reason = "The request was improperly formatted, or the server couldn't understand it.";
        action = ABORT;
        break;
    case HTTP_UNAUTHORIZED:
        reason = "The Authorization header was missing or invalid.";
        action = ABORT;
        break;
    case HTTP_FORBIDDEN:
        reason = "The Authorization token you passed did not have permission to the resource.";
        action = DONE;
        break;
    case HTTP_NOT_FOUND:
        reason = "The resource at the location specified doesn't exist.";
        action = ABORT;
        break;
    case HTTP_METHOD_NOT_ALLOWED:
        reason = "The HTTP method used is not valid for the location specified.";
        action = ABORT;
        break;
    case HTTP_TOO_MANY_REQUESTS:
    /* @todo dealing with ratelimits solely by checking for
     *  HTTP_TOO_MANY REQUESTS is not discord compliant */
     {
        reason = "You got ratelimited.";
        action = RETRY;

        char message[256];
        long long retry_after;

        json_scanf(api->body.str, api->body.size,
                    "[message]%s [retry_after]%lld",
                    message, &retry_after);

        D_NOTOP_PRINT("Ratelimit Message: %s (wait: %lld ms)",
            message, retry_after);

        sleep_ms(retry_after);

        break;
     }
    case HTTP_GATEWAY_UNAVAILABLE:
        reason = "There was not a gateway available to process your request. Wait a bit and retry.";
        action = RETRY;

        sleep_ms(5000); //wait a bit
        break;
    case CURL_NO_RESPONSE:
        reason = "Curl couldn't fetch a HTTP response.";
        action = DONE;
        break;
    default:
        if (code >= 500) {
          reason = "The server had an error processing your request.";
          action = RETRY;
        }
        else {
          reason = "Unknown HTTP method.";
          action = ABORT;
        }

        break;
    }

    switch (action) {
    case DONE:
        //build and updates bucket's rate limiting information
        Discord_ratelimit_build_bucket(api, bucket, endpoint);
    /* fall through */    
    case RETRY:
        D_NOTOP_PRINT("(%d)%s - %s", code, http_code_print(code), reason);

        //reset the size of response body and header pairs for a fresh start
        api->body.size = 0;
        api->pairs.size = 0;

        break;
    case ABORT: default:
        ERROR("(%d)%s - %s", code, http_code_print(code), reason);
    }

  } while (RETRY == action);
}

/* template function for performing requests */
void 
run(
  struct data *api,
  void *p_object,
  load_obj_cb *load_cb,
  char postfields[],
  struct api_resbody_s * body,
  enum http_method method,
  char endpoint[],
  ...)
{
  //create the url route
  va_list args;
  va_start (args, endpoint);
  char url[MAX_URL_LEN];
  int ret = vsnprintf(url, sizeof(url), endpoint, args);
  ASSERT_S(ret < (int) sizeof(url), "oob write of url");
  va_end(args);

  set_method(api->ehandle, method, body); //set the request method
  set_url(api->ehandle, BASE_API_URL, url); //set the request URL
  perform_request(api, p_object, load_cb, endpoint); //perform the request
}

} // namespace api
} // namespace v8
} // namespace discord
