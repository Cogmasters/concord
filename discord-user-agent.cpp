#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <libdiscord.h>
#include "orka-utils.h"

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
                  &ua->resp_body);
}

void
cleanup(dati *ua)
{
  bucket::cleanup(ua);

  curl_slist_free_all(ua->req_header);
  curl_easy_cleanup(ua->ehandle); 

  if (ua->resp_body.start) {
    free(ua->resp_body.start);
  }
}

struct _ratelimit {
  dati *ua;
  bucket::dati *bucket;
  char *endpoint;
};

static void
bucket_cooldown_cb(void *p_data)
{
  struct _ratelimit *data = (struct _ratelimit*)p_data;
  bucket::try_cooldown(data->bucket);
}

static perform_action
on_success_cb(
  void *p_data,
  int httpcode,
  struct sized_buffer *resp_body,
  struct api_header_s *pairs)
{
  D_NOTOP_PRINT("(%d)%s - %s", 
      httpcode,
      http_code_print(httpcode),
      http_reason_print(httpcode));

  struct _ratelimit *data = (struct _ratelimit*)p_data;
  bucket::build(data->ua, data->bucket, data->endpoint);

  return ACTION_DONE;
}

static perform_action
on_failure_cb(
  void *p_data,
  int httpcode,
  struct sized_buffer *resp_body,
  struct api_header_s *pairs)
{
  if (httpcode >= 500) { // server related error, retry
    D_NOTOP_PRINT("(%d)%s - %s", 
        httpcode,
        http_code_print(httpcode),
        http_reason_print(httpcode));

    orka_sleep_ms(5000); // wait arbitrarily 5 seconds before retry

    return ACTION_RETRY; // RETRY
  }

  switch (httpcode) {
  case HTTP_BAD_REQUEST:
  case HTTP_UNAUTHORIZED:
  case HTTP_FORBIDDEN:
  case HTTP_NOT_FOUND:
  case HTTP_METHOD_NOT_ALLOWED:
  default:
      NOTOP_PRINT("(%d)%s - %s",  //print error and abort
          httpcode,
          http_code_print(httpcode),
          http_reason_print(httpcode));

      return ACTION_ABORT;
  case HTTP_TOO_MANY_REQUESTS:
   {
      NOTOP_PRINT("(%d)%s - %s", 
          httpcode,
          http_code_print(httpcode),
          http_reason_print(httpcode));

      char message[256];
      long long retry_after_ms = 0;

      json_scanf(resp_body->start, resp_body->size,
                  "[message]%s [retry_after]%lld",
                  message, &retry_after_ms);

      if (retry_after_ms) { // retry after attribute received
        NOTOP_PRINT("RATELIMIT MESSAGE:\n\t%s (wait: %lld ms)", message, retry_after_ms);

        orka_sleep_ms(retry_after_ms); // wait a bit before retrying

        return ACTION_RETRY;
      }
      
      // no retry after included, we should abort

      NOTOP_PRINT("RATELIMIT MESSAGE:\n\t%s", message);
      return ACTION_ABORT;
   }
  }
}

static void
default_error_cb(char *str, size_t len, void *p_err)
{
  char message[256] = {0};
  int code = 0;

  json_scanf(str, len, "[message]%s [code]%d", message, &code);

  NOTOP_PRINT("Error Description:\n\t\t%s (code %d)"
      "- See Discord's JSON Error Codes", message, code);

  (void)p_err;
}

/* template function for performing requests */
void
run(
  dati *ua, 
  struct resp_handle *resp_handle,
  struct sized_buffer *req_body,
  enum http_method http_method,
  char endpoint[],
  ...)
{
  va_list args;
  va_start (args, endpoint);

  set_url(ua->ehandle, BASE_API_URL, endpoint, args); //set the request URL

  va_end(args);

  set_method(ua->ehandle, http_method, req_body); //set the request method

  struct _ratelimit ratelimit = {
    .ua = ua, 
    .bucket = bucket::try_get(ua, endpoint), 
    .endpoint = endpoint
  };

  struct perform_cbs cbs = {
    .p_data = (void*)&ratelimit,
    .before_perform = &bucket_cooldown_cb,
    .on_1xx = NULL,
    .on_2xx = &on_success_cb,
    .on_3xx = &on_success_cb,
    .on_4xx = &on_failure_cb,
    .on_5xx = &on_failure_cb,
  };

  if (resp_handle && !resp_handle->err_cb) { //set default callback for err_cb
    resp_handle->err_cb = &default_error_cb;
  }

  perform_request(
    resp_handle,
    &ua->resp_body,
    &ua->pairs,
    ua->ehandle,
    &cbs);
}

} // namespace user_agent
} // namespace discord
