#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "github.h"
#include "github-adapter.h"

#include "json-scanf.h"
#include "orka-utils.h"

#define BASE_API_URL   "https://api.github.com"

void
github_adapter_cleanup(struct github_adapter *adapter) {
  ua_cleanup(adapter->ua);
}

static void
curl_easy_setopt_cb(CURL *ehandle, void *data)
{
  struct github_adapter *adapter = data;
  curl_easy_setopt(ehandle, CURLOPT_USERNAME, adapter->username);
  curl_easy_setopt(ehandle, CURLOPT_USERPWD, adapter->token);
}

void
github_adapter_init(struct github_adapter *adapter, char username[], char token[])
{
  adapter->ua = ua_init(BASE_API_URL, NULL);
  ua_reqheader_add(adapter->ua, "Accept", "application/vnd.github.v3+json");

  ua_easy_setopt(adapter->ua, adapter, &curl_easy_setopt_cb);
  adapter->username = username;
  adapter->token = token;
}

/* template function for performing requests */
void github_adapter_run(
  struct github_adapter *adapter,
  struct ua_resp_handle *resp_handle,
  struct sized_buffer *req_body,
  enum http_method http_method,
  char endpoint[],
  ...)
{
  va_list args;
  va_start(args, endpoint);

  ua_vrun(
    adapter->ua,
    NULL,
    resp_handle,
    req_body,
    http_method, endpoint, args);

  va_end(args);
}
