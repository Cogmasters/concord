#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "github.h"
#include "github-internal.h"

#include "cee-utils.h"

#define GITHUB_BASE_API_URL "https://api.github.com"

void
github_adapter_cleanup(struct github_adapter *adapter)
{
  ua_cleanup(adapter->ua);
}

static void
curl_easy_setopt_cb(CURL *ehandle, void *data)
{
  struct github_presets *presets = data;
  curl_easy_setopt(ehandle, CURLOPT_USERNAME, presets->username);
  curl_easy_setopt(ehandle, CURLOPT_USERPWD, presets->token);
}

void
github_adapter_init(struct github_adapter *adapter,
                    struct logconf *conf,
                    struct github_presets *presets)
{
  adapter->ua = ua_init(conf);
  ua_set_url(adapter->ua, GITHUB_BASE_API_URL);
  ua_reqheader_add(adapter->ua, "Accept", "application/vnd.github.v3+json");
  ua_curl_easy_setopt(adapter->ua, presets, &curl_easy_setopt_cb);
}

static void
__log_error(char *str, size_t len, void *p)
{
  log_error("%.*s", (int)len, str);
}

/* template function for performing requests */
ORCAcode
github_adapter_run(struct github_adapter *adapter,
                   struct ua_resp_handle *resp_handle,
                   struct sized_buffer *req_body,
                   enum http_method http_method,
                   char endpoint_fmt[],
                   ...)
{
  va_list args;
  char endpoint[2048];

  va_start(args, endpoint_fmt);
  int ret = vsnprintf(endpoint, sizeof(endpoint), endpoint_fmt, args);
  ASSERT_S(ret < sizeof(endpoint), "Out of bounds write attempt");

  /* IF UNSET, SET TO DEFAULT ERROR HANDLING CALLBACKS */
  if (resp_handle && !resp_handle->err_cb) {
    resp_handle->err_cb = &__log_error;
    resp_handle->err_obj = NULL;
  }

  ORCAcode code;
  code =
    ua_run(adapter->ua, NULL, resp_handle, req_body, http_method, endpoint);

  va_end(args);

  return code;
}
