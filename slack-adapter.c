#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "slack.h"
#include "slack-internal.h"
#include "orka-utils.h"

#define BASE_API_URL "https://slack.com/api"


void
slack_adapter_init(struct slack_adapter *adapter, struct logconf *config, struct sized_buffer *token)
{
  adapter->ua = ua_init(BASE_API_URL, config);
  logconf_add_id(config, adapter->ua, "SLACK_WEBAPI");

  if (STRNEQ("YOUR-BOT-TOKEN", token->start, token->size)) {
    token->start = NULL;
  }
  ASSERT_S(NULL != token->start, "Missing bot token");

  char auth[128];
  int ret = snprintf(auth, sizeof(auth), "Bearer %.*s", (int)token->size, token->start);
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
