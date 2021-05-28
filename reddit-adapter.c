#define _GNU_SOURCE /* asprintf() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "reddit.h"
#include "reddit-internal.h"
#include "orka-utils.h"


static void
curl_setopt_cb(CURL *ehandle, void *p_client)
{
  struct reddit *client = p_client;

  int ret; // check return length
  char client_id[512], client_secret[512];
  ret = snprintf(client_id, sizeof(client_id), "%.*s", (int)client->client_id.size, client->client_id.start);
  ASSERT_S(ret < sizeof(client_id), "Out of bounds write attempt");
  ret = snprintf(client_secret, sizeof(client_secret), "%.*s", (int)client->client_secret.size, client->client_secret.start);
  ASSERT_S(ret < sizeof(client_secret), "Out of bounds write attempt");

  CURLcode ecode;
  ecode = curl_easy_setopt(ehandle, CURLOPT_USERNAME, client_id);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
  ecode = curl_easy_setopt(ehandle, CURLOPT_PASSWORD, client_secret);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
}

void
reddit_adapter_init(struct reddit_adapter *adapter, struct logconf *config)
{
  adapter->ua = ua_init(config);
  ua_set_url(adapter->ua, BASE_API_URL);
  logconf_add_id(config, adapter->ua, "REDDIT_HTTP");

  ua_easy_setopt(adapter->ua, adapter->p_client, &curl_setopt_cb);

  ua_reqheader_add(adapter->ua, "User-Agent", "orca:github.com/cee-studio/orca:v.0 (by /u/LucasMull)");
  ua_reqheader_add(adapter->ua, "Content-Type", "application/x-www-form-urlencoded");
}

void
reddit_adapter_cleanup(struct reddit_adapter *adapter) {
  ua_cleanup(adapter->ua);
}

static void
get_response(char *str, size_t len, void *p_json)
{
  struct sized_buffer *json = p_json;
  asprintf(&json->start, "%.*s", (int)len, str);
  json->size = len;
}

/* template function for performing requests */
ORCAcode
reddit_adapter_run(
  struct reddit_adapter *adapter, 
  struct sized_buffer *resp_body,
  struct sized_buffer *req_body,
  enum http_method http_method, char endpoint[], ...)
{
  va_list args;
  va_start(args, endpoint);

  struct ua_resp_handle resp_handle = {
    .ok_cb = resp_body ? &get_response : NULL,
    .ok_obj = resp_body,
  };

  ORCAcode code;

  code = ua_vrun(
           adapter->ua,
           NULL,
           &resp_handle,
           req_body,
           http_method, endpoint, args);

  va_end(args);

  return code;
}
