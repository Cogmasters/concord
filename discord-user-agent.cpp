#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <libdiscord.h>
#include "orka-utils.h"

#define BASE_API_URL "https://discord.com/api"

namespace discord {
namespace user_agent {

void
init(dati *ua, const char token[], const char config_file[])
{
  if (config_file) {
    ua_init_config(&ua->common, BASE_API_URL, "DISCORD HTTP", config_file);
    token = ua->common.debug.token;
  }

  char auth[128];
  int ret = snprintf(auth, sizeof(auth), "Bot %s", ua->common.debug.token);
  ASSERT_S(ret < (int)sizeof(auth), "Out of bounds write attempt");

  ua_reqheader_add(&ua->common, "Authorization", auth);
  ua_reqheader_add(&ua->common, "X-RateLimit-Precision", "millisecond");
}

void
cleanup(dati *ua)
{
  bucket::cleanup(ua);
  ua_cleanup(&ua->common);
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
  struct ua_conn_s *conn)
{
  DS_NOTOP_PRINT("(%d)%s - %s", 
      httpcode,
      http_code_print(httpcode),
      http_reason_print(httpcode));

  struct _ratelimit *data = (struct _ratelimit*)p_data;
  bucket::build(data->ua, data->bucket, data->endpoint, conn);

  return ACTION_SUCCESS;
}

static perform_action
on_failure_cb(
  void *p_data,
  int httpcode,
  struct ua_conn_s *conn)
{
  if (httpcode >= 500) { // server related error, retry
    NOTOP_PRINT("(%d)%s - %s", 
        httpcode,
        http_code_print(httpcode),
        http_reason_print(httpcode));

    orka_sleep_ms(5000); // wait arbitrarily 5 seconds before retry

    return ACTION_RETRY; // RETRY
  }

  switch (httpcode) {
  case HTTP_FORBIDDEN:
  case HTTP_NOT_FOUND:
  case HTTP_BAD_REQUEST:
      NOTOP_PRINT("(%d)%s - %s",  //print error and continue
          httpcode,
          http_code_print(httpcode),
          http_reason_print(httpcode));

      return ACTION_FAILURE;
  case HTTP_UNAUTHORIZED:
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

      json_scanf(conn->resp_body.start, conn->resp_body.size,
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
  struct error *err = (struct error*)p_err;

  json_scanf(str, len, "[message]%s [code]%d", 
      err->message, &err->code);

  NOTOP_PRINT("Error Description:\n\t\t%s (code %d)"
      "- See Discord's JSON Error Codes", err->message, err->code);
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
  va_start(args, endpoint);

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

  /* IF UNSET, SET TO DEFAULT ERROR HANDLING CALLBACKS */
  if (resp_handle && !resp_handle->err_cb) {
    resp_handle->err_cb = &default_error_cb;
    resp_handle->err_obj = (void*)&ua->json_err; //overrides existing obj
  }

  ua_vrun(
    &ua->common,
    resp_handle,
    req_body,
    &cbs,
    http_method, endpoint, args);

  va_end(args);
}

} // namespace user_agent
} // namespace discord
