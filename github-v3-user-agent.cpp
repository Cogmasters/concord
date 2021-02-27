#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "github-v3.hpp"

#include "json-scanf.h"
#include "orka-utils.h"

#define BASE_API_URL   "https://api.github.com"

namespace github {
namespace v3 { 
namespace user_agent {

void
cleanup(struct dati *ua) {
  orka::user_agent::cleanup(&ua->common);
}

static void
curl_easy_setopt_cb(CURL *ehandle, void *data)
{
  dati *ua = (dati*)data;
  curl_easy_setopt(ehandle, CURLOPT_USERNAME, ua->username);
  curl_easy_setopt(ehandle, CURLOPT_USERPWD, ua->token);
}

void
init(struct dati *ua, char username[], char token[])
{
  ua_easy_setopt(&ua->common, ua, &curl_easy_setopt_cb);

  char user_agent[] = "orca (http://github.com/cee-studio/orca)";
  ua->username = username;
  ua->token = token;

  add_reqheader_pair(&ua->common, "Content-Type", "application/json");
  add_reqheader_pair(&ua->common, "Accept", "application/vnd.github.v3+json");
  add_reqheader_pair(&ua->common, "User-Agent", user_agent);

}

/* template function for performing requests */
void run(
  struct dati *ua,
  struct resp_handle *resp_handle,
  struct sized_buffer *req_body,
  enum http_method http_method,
  char endpoint[],
  ...)
{
  va_list args;
  va_start(args, endpoint);

  orka::user_agent::vrun(
    &ua->common,
    resp_handle,
    req_body,
    NULL,
    http_method, endpoint, args);

  va_end(args);
}

} // namespace user_agent
} // namespace v3
} // namespace github
