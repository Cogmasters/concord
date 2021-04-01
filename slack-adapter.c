#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "slack.h"
#include "slack-common.h"
#include "orka-utils.h"

#define BASE_API_URL "https://slack.com/api"


void
slack_adapter_init(struct slack_adapter *adapter, const char config_file[])
{
  ASSERT_S(NULL != config_file, "Missing config file");

  adapter->ua = ua_config_init(BASE_API_URL, "SLACK HTTP", config_file);
  struct sized_buffer token = ua_config_get_field(adapter->ua, "slack.bot-token");
  ASSERT_S(NULL != token.start, "Missing bot token");

  char auth[128];
  int ret = snprintf(auth, sizeof(auth), "Bearer %.*s", (int)token.size, token.start);
  ASSERT_S(ret < sizeof(auth), "Out of bounds write attempt");

  ua_reqheader_add(adapter->ua, "Authorization", auth);
  ua_reqheader_add(adapter->ua, "Content-type", "application/x-www-form-urlencoded");
}

void
slack_adapter_cleanup(struct slack_adapter *adapter)
{
  ua_cleanup(adapter->ua);
}

/* template function for performing requests */
void
slack_adapter_run(
  struct slack_adapter *adapter, 
  struct resp_handle *resp_handle,
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

