#define _GNU_SOURCE /* asprintf() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "slack.h"
#include "slack-internal.h"
#include "cee-utils.h"

#define SLACK_BASE_API_URL "https://slack.com/api"

void
slack_webapi_init(struct slack_webapi *webapi,
                  struct logconf *conf,
                  struct sized_buffer *token)
{
  webapi->ua = ua_init(conf);
  ua_set_url(webapi->ua, SLACK_BASE_API_URL);
  logconf_branch(&webapi->conf, conf, "SLACK_WEBAPI");

  if (STRNEQ("YOUR-BOT-TOKEN", token->start, token->size)) {
    token->start = NULL;
  }
  ASSERT_S(NULL != token->start, "Missing bot token");

  char auth[128];
  int ret = snprintf(auth, sizeof(auth), "Bearer %.*s", (int)token->size,
                     token->start);
  ASSERT_S(ret < sizeof(auth), "Out of bounds write attempt");

  ua_reqheader_add(webapi->ua, "Authorization", auth);
  ua_reqheader_add(webapi->ua, "Content-type",
                   "application/x-www-form-urlencoded");
}

void
slack_webapi_cleanup(struct slack_webapi *webapi)
{
  ua_cleanup(webapi->ua);
}

static void
sized_buffer_from_json(char *json, size_t len, void *data)
{
  struct sized_buffer *p = data;
  p->size = asprintf(&p->start, "%.*s", (int)len, json);
}

/* template function for performing requests */
ORCAcode
slack_webapi_run(struct slack_webapi *webapi,
                 struct sized_buffer *resp_body,
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

  ORCAcode code;
  code = ua_run(webapi->ua, NULL,
                &(struct ua_resp_handle){
                  .ok_cb = resp_body ? &sized_buffer_from_json : NULL,
                  .ok_obj = resp_body },
                req_body, http_method, endpoint);

  va_end(args);

  return code;
}
