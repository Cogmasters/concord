#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "orka-user-agent.hpp"
#include "orka-utils.h"

namespace orka {
namespace user_agent {

void
init(dati *ua, char *base_url)
{
  ua_handle_init(ua, base_url);

  char user_agent[] = "orca (http://github.com/cee-studio/orca)";

  add_reqheader_pair(ua, "Accept", "application/json");
  add_reqheader_pair(ua, "Content-Type", "application/json");
  add_reqheader_pair(ua, "User-Agent", user_agent);
}

void
cleanup(dati *ua)
{
  ua_handle_cleanup(ua);
}

/* template function for performing requests */
void 
vrun(
  dati *ua,
  struct resp_handle *resp_handle,
  struct sized_buffer *req_body,
  struct perform_cbs *cbs,
  enum http_method http_method,
  char endpoint[],
  va_list args)
{
  struct ua_conn_s *conn = ua_get_conn(ua);
  ua_set_url(conn, ua->base_url, endpoint, args);
  ua_set_method(conn, http_method, req_body); //set the request method
  ua_perform_request(conn, resp_handle, cbs);

  ++ua->num_available; //@todo this should happen at http-common
}

/* template function for performing requests */
void 
run(
  dati *ua,
  struct resp_handle *resp_handle,
  struct sized_buffer *req_body,
  struct perform_cbs *cbs,
  enum http_method http_method,
  char endpoint[],
  ...)
{
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
