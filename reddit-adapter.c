#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "reddit.h"
#include "reddit-common.h"
#include "orka-utils.h"

#define BASE_API_URL "https://www.reddit.com/api/v1"


void
reddit_adapter_config_init(struct reddit_adapter *adapter, const char config_file[])
{
  ASSERT_S(NULL != config_file, "Missing config file");

  adapter->ua = ua_config_init(BASE_API_URL, "REDDIT HTTP", config_file);
}

void
reddit_adapter_cleanup(struct reddit_adapter *adapter) {
  ua_cleanup(adapter->ua);
}

/* template function for performing requests */
void
reddit_adapter_run(
  struct reddit_adapter *adapter, 
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
