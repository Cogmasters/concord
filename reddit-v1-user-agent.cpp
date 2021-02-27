#include <stdarg.h>

#include "orka-user-agent.hpp"
#include "reddit-v1-user-agent.hpp"

#define BASE_API_URL   "https://www.reddit.com/api/v1"

namespace reddit {
namespace v1 {
namespace user_agent {


void
init(struct dati *ua, char *username, char *password)
{
  ua_init(&ua->common, BASE_API_URL);
  ua->username =  username;
}

/* template function for performing requests */
void 
run(
  struct dati *ua,
  struct resp_handle *resp_handle,
  struct sized_buffer *req_body,
  enum http_method http_method,
  char endpoint[],
  ...)
{
  //create the url route
  va_list args;
  va_start (args, endpoint);

  orka::user_agent::vrun(
    &ua->common, 
    resp_handle, 
    req_body, 
    http_method, endpoint, args);

  va_end(args);
}

} // namespace user_agent
} // namespace v1
} // namespace reddit
