#include <stdarg.h>

#include "user-agent.h"
#include "websockets.h"
#include "orka-utils.h"
#include "reddit.h"

#define BASE_API_URL   "https://www.reddit.com/api/v1"


void
reddit_user_agent_init(struct dati *ua, char *username, char *password)
{
#if 0
  ua_init(&ua->common, BASE_API_URL);
  ua->username =  username;
#endif
}

/* template function for performing requests */
void 
reddit_user_agent_run(
  struct reddit_user_agent *ua,
  struct resp_handle *resp_handle,
  struct sized_buffer *req_body,
  enum http_method http_method,
  char endpoint[],
  ...)
{
  //create the url route
  va_list args;
  va_start (args, endpoint);

  ua_vrun(
    &ua->common, 
    resp_handle, 
    req_body, 
    http_method, endpoint, args);

  va_end(args);
}