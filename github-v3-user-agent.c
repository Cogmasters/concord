#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "github-v3.h"

#include "json-scanf.h"
#include "orka-utils.h"

#define BASE_API_URL   "https://api.github.com"

//namespace github {
//namespace v3 { 
//namespace user_agent {

void
github_v3_user_agent_cleanup(struct github_v3_user_agent_dati *ua) {
  ua_cleanup(&ua->common);
}

static void
curl_easy_setopt_cb(CURL *ehandle, void *data)
{
  struct github_v3_user_agent_dati *ua = (struct github_v3_user_agent_dati*)data;
  curl_easy_setopt(ehandle, CURLOPT_USERNAME, ua->username);
  curl_easy_setopt(ehandle, CURLOPT_USERPWD, ua->token);
}

void
github_v3_user_agent_init(struct github_v3_user_agent_dati *ua, char username[], char token[])
{
  ua_init(&ua->common, BASE_API_URL);
  ua_reqheader_add(&ua->common, "Accept", "application/vnd.github.v3+json");

  ua_easy_setopt(&ua->common, ua, &curl_easy_setopt_cb);
  ua->username = username;
  ua->token = token;
}

/* template function for performing requests */
void github_v3_user_agent_run(
  struct github_v3_user_agent_dati *ua,
  struct resp_handle *resp_handle,
  struct sized_buffer *req_body,
  enum http_method http_method,
  char endpoint[],
  ...)
{
  va_list args;
  va_start(args, endpoint);

  ua_vrun(
    &ua->common,
    resp_handle,
    req_body,
    NULL,
    http_method, endpoint, args);

  va_end(args);
}

//} // namespace user_agent
//} // namespace v3
//} // namespace github
