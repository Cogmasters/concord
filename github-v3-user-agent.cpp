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

static struct curl_slist*
reqheader_init()
{
  struct curl_slist *new_header = NULL;

  new_header = curl_slist_append(new_header, "Accept: application/vnd.github.v3+json");
  curl_slist_append(new_header, "Content-Type: application/json");
  curl_slist_append(new_header, "User-Agent: orka");

  return new_header;
}

void
cleanup(struct dati *ua)
{
  curl_slist_free_all(ua->req_header);
  curl_easy_cleanup(ua->ehandle);

  if (ua->resp_body.start) {
    free(ua->resp_body.start);
  }
}

void
init(struct dati *ua, char username[], char token[])
{
  ua->req_header = reqheader_init();
  ua->ehandle = custom_easy_init(&ua->settings,
                                  ua->req_header,
                                  &ua->pairs,
                                  &ua->resp_body);

  curl_easy_setopt(ua->ehandle, CURLOPT_USERNAME, username);
  curl_easy_setopt(ua->ehandle, CURLOPT_USERPWD, token);
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

  set_url(ua->ehandle, BASE_API_URL, endpoint, args); //set the request URL

  va_end(args);

  set_method(ua->ehandle, http_method, req_body); //set the request method
  
  //@todo this is a temporary solution
  struct perform_cbs cbs = {NULL};
  
  //perform the request
  perform_request(
    resp_handle, 
    &ua->resp_body,
    &ua->pairs, 
    ua->ehandle, 
    &cbs);
}

} // namespace user_agent
} // namespace v3
} // namespace github
