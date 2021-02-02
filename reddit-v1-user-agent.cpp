#include <stdarg.h>
#include "orka-user-agent.hpp"
#include "reddit-v1-user-agent.hpp"

#define BASE_API_URL   "https://www.reddit.com/api/v1"

namespace reddit {
namespace v1 {
namespace user_agent {


void
init(struct dati *d, char *username, char *password)
{
  orka::user_agent::init(d->ua, BASE_API_URL);
  d->username =  username;
}

/* template function for performing requests */
void 
run(
  struct dati *api,
  struct resp_handle *resp_handle,
  struct sized_buffer *response_body,
  enum http_method http_method,
  char endpoint[],
  ...)
{
  //create the url route
  va_list args;
  va_start (args, endpoint);

  orka::user_agent::vrun(
    api->ua, 
    resp_handle, 
    response_body, 
    http_method, 
    endpoint, 
    args);

  va_end(args);
}

} // namespace user_agent
} // namespace v1
} // namespace reddit
