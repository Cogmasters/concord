#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "orka-user-agent.hpp"
#include "orka-utils.h"

namespace orka {
namespace user_agent {

static struct curl_slist*
reqheader_init()
{
  char user_agent[] = "orka (http://github.com/cee-studio/orca)";

  struct curl_slist *new_header = NULL;
  add_reqheader_pair(&new_header, "Accept", "application/json");
  add_reqheader_pair(&new_header, "Content-Type", "application/json");
  add_reqheader_pair(&new_header, "User-Agent", user_agent);

  return new_header;
}

void
init(struct dati *ua, char *base_url)
{
  memset(ua, 0, sizeof(struct dati));
  ua->req_header = reqheader_init();
  ua->ehandle = custom_easy_init(&(ua->settings),
                                  ua->req_header,
                                  &ua->pairs,
                                  &ua->resp_body);
  ua->base_url = base_url;
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

/* template function for performing requests */
void 
vrun(
  struct dati *ua,
  struct resp_handle *resp_handle,
  struct sized_buffer *req_body,
  struct perform_cbs *cbs,
  enum http_method http_method,
  char endpoint[],
  va_list args)
{
  set_url(ua->ehandle, ua->base_url, endpoint, args);

  set_method(ua->ehandle, http_method, req_body); //set the request method
  
  //perform the request
  perform_request(
    resp_handle, 
    &ua->resp_body, 
    &ua->pairs, 
    ua->ehandle,
    cbs);
}

/* template function for performing requests */
void 
run(
  struct dati *ua,
  struct resp_handle *resp_handle,
  struct sized_buffer *req_body,
  struct perform_cbs *cbs,
  enum http_method http_method,
  char endpoint[],
  ...)
{
  //create the url route
  va_list args;
  va_start(args, endpoint);

  vrun(
    ua, 
    resp_handle, 
    req_body, 
    cbs, 
    http_method, endpoint, args);

  va_end(args);
}

} // namespace user_agent
} // namespace orka
