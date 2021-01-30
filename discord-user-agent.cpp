#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h> //for usleep
#include <stdarg.h>

#include <libdiscord.h>

#define BASE_API_URL "https://discord.com/api"

namespace discord {
namespace user_agent {

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

  tmp = curl_slist_append(new_header,"User-Agent: orca (http://github.com/cee-studio/orca, v" LIBDISCORD_VERSION ")");
  ASSERT_S(NULL != tmp, "Out of memory");

  tmp = curl_slist_append(new_header,"Content-Type: application/json");
  ASSERT_S(NULL != tmp, "Out of memory");

  return new_header;
}

void
init(dati *ua, char token[])
{
  ua->req_header = reqheader_init(token);
  ua->ehandle = custom_easy_init(
                  &ua->p_client->settings,
                  ua->req_header,
                  &ua->pairs,
                  &ua->body);
}

void
cleanup(dati *ua)
{
  bucket::cleanup(ua);

  curl_slist_free_all(ua->req_header);
  curl_easy_cleanup(ua->ehandle); 

  if (ua->body.start) {
    free(ua->body.start);
  }
}

/* perform the request */
static http_code
perform_request(
  dati *ua,
  struct resp_handle *resp_handle,
  char endpoint[])
{ 
  CURLcode ecode;
  //perform the connection
  ecode = curl_easy_perform(ua->ehandle);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //get response's code
  enum http_code code;
  ecode = curl_easy_getinfo(ua->ehandle, CURLINFO_RESPONSE_CODE, &code);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //get request's url
  const char *url = NULL;
  ecode = curl_easy_getinfo(ua->ehandle, CURLINFO_EFFECTIVE_URL, &url);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  D_PRINT("Request URL: %s", url);

  return code;
}

/* template function for performing requests */
void
run(
  dati *ua, 
  struct resp_handle *resp_handle,
  struct sized_buffer *body,
  enum http_method http_method,
  char endpoint[],
  ...)
{
  //create the url route
  va_list args;
  va_start (args, endpoint);
  char url_route[MAX_URL_LEN];
  int ret = vsnprintf(url_route, sizeof(url_route), endpoint, args);
  ASSERT_S(ret < (int)sizeof(url_route), "oob write of url_route");
  va_end(args);

  set_method(ua->ehandle, http_method, body); //set the request method
  set_url(ua->ehandle, BASE_API_URL, url_route); //set the request URL

  //attempt to fetch a bucket handling connections from this endpoint
  bucket::dati *bucket = bucket::try_get(ua, endpoint);
  enum http_code http_code;
  do {
    if (bucket) { //bucket exists, we will check for pending delays
      long long delay_ms = bucket::cooldown(bucket, true);
      D_PRINT("RATELIMITING (reach bucket's connection threshold):\n\t"
              "\tEndpoint:\t%s\n\t"
              "\tBucket:\t\t%s\n\t"
              "\tWait for:\t%lld ms",
              endpoint, bucket->hash, delay_ms);

      sleep_ms(delay_ms); //sleep for delay amount (if any)
    }
  
    http_code = perform_request(ua, resp_handle, endpoint); //perform the request
    switch (http_code) {

/* THE FOLLOWING WILL SUCCESFULLY RETURN */

    case HTTP_OK:
        if (resp_handle->ok_cb) {
          (*resp_handle->ok_cb)(ua->body.start, ua->body.len, resp_handle->ok_obj);
        }
    /* fall through */
    case HTTP_CREATED:
    case HTTP_NO_CONTENT:
    case HTTP_NOT_MODIFIED:
    case CURL_NO_RESPONSE:
        D_NOTOP_PRINT("(%d)%s - %s", 
            http_code,
            http_code_print(http_code),
            http_reason_print(http_code));

        //build and updates bucket's rate limiting information
        bucket::build(ua, bucket, endpoint);

        //reset the size of response body and header pairs for a fresh start
        ua->body.len = 0;
        ua->pairs.size = 0;

        return; //EARLY EXIT (SUCCESS)

/* THE FOLLOWING WILL ATTEMPT RETRY WHEN TRIGGERED */

    case HTTP_TOO_MANY_REQUESTS:
     {
        D_NOTOP_PRINT("(%d)%s - %s", 
            http_code,
            http_code_print(http_code),
            http_reason_print(http_code));

        char message[256];
        long long retry_after = 0;

        json_scanf(ua->body.start, ua->body.len,
                    "[message]%s [retry_after]%lld",
                    message, &retry_after);

        if (retry_after) // retry after attribute received
          D_NOTOP_PRINT("Ratelimit Message: %s (wait: %lld ms)", message, retry_after);
        else // no retry after included, we should abort
          ERR("Ratelimit Message: %s", message);

        sleep_ms(retry_after);

        break;
     }
    case HTTP_GATEWAY_UNAVAILABLE:
        D_NOTOP_PRINT("(%d)%s - %s", 
            http_code,
            http_code_print(http_code),
            http_reason_print(http_code));

        sleep_ms(5000); //wait a bit

        break;

/* THE FOLLOWING WILL ABORT WHEN TRIGGERED */

    case HTTP_BAD_REQUEST:
    case HTTP_UNAUTHORIZED:
    case HTTP_FORBIDDEN:
    case HTTP_NOT_FOUND:
    case HTTP_METHOD_NOT_ALLOWED:
    default:
        if (http_code >= 500) {// server related error, retry
          D_NOTOP_PRINT("(%d)%s - %s", 
              http_code,
              http_code_print(http_code),
              http_reason_print(http_code));
          break;
        }

        ERR("(%d)%s - %s", 
            http_code,
            http_code_print(http_code),
            http_reason_print(http_code));
    }

    //reset the size of response body and header pairs for a fresh start
    
    ua->body.len = 0;
    ua->pairs.size = 0;

  } while (1);
}

} // namespace user_agent
} // namespace discord
