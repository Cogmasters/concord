#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <stddef.h>

#include "orka-user-agent.hpp"

#include "orka-utils.h"
#include "json-scanf.h"

namespace orka {
namespace user_agent {

static struct curl_slist*
reqheader_init()
{
  struct curl_slist *new_header = NULL;
  new_header = curl_slist_append(new_header, "Accept: application/json");
  curl_slist_append(new_header, "Content-Type: application/json");
  curl_slist_append(new_header, "User-Agent: curl");
  return new_header;
}

void
cleanup(struct dati *api)
{
  curl_slist_free_all(api->req_header);
  curl_easy_cleanup(api->ehandle);

  if (api->body.start) {
    free(api->body.start);
  }
}

void
init(struct dati *api, char * base_url)
{
  api->req_header = reqheader_init();
  api->ehandle = custom_easy_init(&(api->settings),
                                  api->req_header,
                                  &api->pairs,
                                  &api->body);
  api->base_url = base_url;
}


/* perform the request */
static void
perform_request(
  struct dati *api,
  struct resp_handle *handle,
  char endpoint[])
{
  enum { //possible actions taken after a http response code
    DONE, RETRY, ABORT
  } action;

  do {
    //perform the connection
    curl_easy_perform(api->ehandle);

    //get response's code
    enum http_code code;
    curl_easy_getinfo(api->ehandle, CURLINFO_RESPONSE_CODE, &code);

    //get request's url
    const char *url = NULL;
    curl_easy_getinfo(api->ehandle, CURLINFO_EFFECTIVE_URL, &url);

    D_PRINT("Request URL: %s", url);

    const char *reason; //verbose reason of http code
    switch (code) {
      case HTTP_OK:
        reason = "The request was completed succesfully.";
        action = DONE;

        if (handle && handle->ok_cb) {
          (*handle->ok_cb)(api->body.start, api->body.size, handle->ok_obj);
        }

        break;
      case HTTP_CREATED:
        reason = "The entity was created succesfully.";
        action = DONE;
        if (handle && handle->ok_cb) {
          (*handle->ok_cb)(api->body.start, api->body.size, handle->ok_obj);
        }
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

        json_scanf(api->body.start, api->body.size,
                   "[message]%s [retry_after]%lld",
                   message, &retry_after);

        D_NOTOP_PRINT("Ratelimit Message: %s (wait: %lld ms)",
                      message, retry_after);

        orka_sleep_ms(retry_after);

        break;
      }
      case HTTP_GATEWAY_UNAVAILABLE:
        reason = "There was not a gateway available to process your request. Wait a bit and retry.";
        action = RETRY;

        orka_sleep_ms(5000); //wait a bit
        break;
      case CURL_NO_RESPONSE:
        reason = "Curl couldn't fetch a HTTP response.";
        action = DONE;
        break;
      default:
        if (code >= 500) {
          reason = "The server had an error processing your request.";
          action = RETRY;
        } else {
          reason = "Unknown HTTP method.";
          action = ABORT;
        }

        break;
    }

    switch (action) {
      case DONE:
        //build and updates bucket's rate limiting information
        //Discord_ratelimit_build_bucket(api, bucket, endpoint);
        /* fall through */
      case RETRY:
        D_NOTOP_PRINT("(%d)%s - %s", code, http_code_print(code),
                      reason);

        //reset the size of response body and header pairs for a fresh start
        api->body.size = 0;
        api->pairs.size = 0;

        break;
      case ABORT:
        if (handle && handle->err_cb) {
          (*handle->err_cb)(api->body.start, api->body.size, handle->err_obj);
        }
      default:
        ERR("(%d)%s - %s", code, http_code_print(code), reason);
    }
  } while (RETRY == action);
}

/* template function for performing requests */
void vrun(struct dati *api,
          struct resp_handle * resp_handle,
          struct sized_buffer * body,
          enum http_method http_method,
          char endpoint[],
          va_list args)
{
  char url_route[MAX_URL_LEN];
  int ret = vsnprintf(url_route, sizeof(url_route), endpoint, args);
  ASSERT_S(ret < (int) sizeof(url_route), "oob write of url_route");

  set_method(api->ehandle, http_method, body); //set the request method
  set_url(api->ehandle, api->base_url, url_route); //set the request URL

  perform_request(api, resp_handle, endpoint); //perform the request
}

/* template function for performing requests */
void run(struct dati *api,
         struct resp_handle * resp_handle,
         struct sized_buffer * body,
         enum http_method http_method,
         char endpoint[],
         ...)
{
  //create the url route
  va_list args;
  va_start (args, endpoint);
  vrun(api, resp_handle, body, http_method, endpoint, args);
  va_end(args);
}

} // namespace user_agent
} // namespace cee
