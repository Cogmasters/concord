#define _GNU_SOURCE /* asprintf() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mujs.h"
#include "js-addons.h"


ORCAcode js_ua_run(
  js_State *J, 
  struct user_agent *ua, 
  struct sized_buffer *resp_body,
  int *p_nparam)
{
  int nparam = js_gettop(J);
  *p_nparam = nparam;
  log_debug("n# of parameters: %d", nparam);

  enum http_method method;
  if (!js_isstring(J, 1)) {
    log_fatal("expect a METHOD string");
    exit(1);
  }
  if (!js_isstring(J, 2)) {
    log_fatal("expect a URL string");
    exit(1);
  }

  char *strmethod = (char *)js_tostring(J, 1);
  log_debug("method: %s", strmethod);
  method = http_method_eval(strmethod);

  char *endpoint = (char *)js_tostring(J, 2);
  log_debug("endpoint: %s", endpoint);

  struct sized_buffer req_body={};
  if (4 == nparam) { // has body
    if (js_isobject(J, 3) || js_isstring(J, 3)) {
      req_body.start = (char *)js_tostring(J, 3);
      req_body.size = strlen(req_body.start);
      log_debug("request body: %.*s", (int)req_body.size, req_body.start);
    }
  }

  struct ua_info info={}; // extract transfer info
  ORCAcode code = ua_run(
                    ua, 
                    &info, 
                    NULL, 
                    &req_body, 
                    method, endpoint, "");

  *resp_body = ua_info_get_resp_body(&info);

  return code;
}
