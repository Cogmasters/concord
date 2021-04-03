#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "reddit.h"
#include "reddit-common.h"
#include "orka-utils.h"

#define BASE_API_URL "https://www.reddit.com/api/v1"


static void
curl_setopt_cb(CURL *ehandle, void *p_ua)
{
  struct user_agent *ua = p_ua;

  struct sized_buffer tclient_id = ua_config_get_field(ua, "reddit.client_id");
  ASSERT_S(NULL != tclient_id.start, "Missing client_id");
  struct sized_buffer tclient_secret = ua_config_get_field(ua, "reddit.client_secret");
  ASSERT_S(NULL != tclient_secret.start, "Missing client_secret");

  int ret; // check return length
  char client_id[512], client_secret[512];
  ret = snprintf(client_id, sizeof(client_id), "%.*s", (int)tclient_id.size, tclient_id.start);
  ASSERT_S(ret < sizeof(client_id), "Out of bounds write");
  ret = snprintf(client_secret, sizeof(client_secret), "%.*s", (int)tclient_secret.size, tclient_secret.start);

  ASSERT_S(ret < sizeof(client_secret), "Out of bounds write");

  CURLcode ecode;
  ecode = curl_easy_setopt(ehandle, CURLOPT_USERNAME, client_id);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  ecode = curl_easy_setopt(ehandle, CURLOPT_PASSWORD, client_secret);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
}

void
reddit_adapter_config_init(struct reddit_adapter *adapter, const char config_file[])
{
  ASSERT_S(NULL != config_file, "Missing config file");

  adapter->ua = ua_config_init(BASE_API_URL, "REDDIT HTTP", config_file);
  ua_easy_setopt(adapter->ua, adapter->ua, &curl_setopt_cb);
}

void
reddit_adapter_cleanup(struct reddit_adapter *adapter) {
  ua_cleanup(adapter->ua);
}

/* template function for performing requests */
void
reddit_adapter_run(
  struct reddit_adapter *adapter, 
  struct ua_resp_handle *resp_handle,
  struct sized_buffer *req_body,
  enum http_method http_method, char endpoint[], ...)
{
  va_list args;
  va_start(args, endpoint);

  ua_vrun(
    adapter->ua,
    resp_handle,
    req_body,
    NULL,
    http_method, endpoint, args);

  va_end(args);
}
