#define _GNU_SOURCE /* asprintf() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mujs.h"
#include "user-agent.h"


static void 
respbody_copy_cb(char *start, size_t size, void *p_body)
{
  char **body = p_body;
  asprintf(body, "%.*s", (int)size, start);
}

ORCAcode orcajs_run(
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

  char *strmethod = (char *)js_tostring(J, 1);
  log_debug("method: %s", strmethod);
  method = http_method_eval(strmethod);

  if (!js_isstring(J, 2)) {
    log_fatal("expect a URL string");
    exit(1);
  }

  char *url = (char *)js_tostring(J, 2);
  log_debug("url: %s", url);

  char *buf=NULL;
  struct ua_resp_handle  resp_handle = \
    { .ok_cb = respbody_copy_cb, .ok_obj = &buf };

  struct sized_buffer req_body={};
  if (4 == nparam) { // has body
    if (js_isobject(J, 3) || js_isstring(J, 3)) {
      req_body.start = (char *)js_tostring(J, 3);
      req_body.size = strlen(req_body.start);
      log_debug("request body: %.*s", (int)req_body.size, req_body.start);
    }
  }

  struct ua_info info={}; // can be used to extract info on the transfer
  ORCAcode code = ua_vrun(
                    ua, 
                    &info, 
                    &resp_handle, 
                    &req_body, 
                    method, url, NULL);

  *resp_body = (struct sized_buffer){
    .start = buf,
    .size = buf ? strlen(buf) : 0
  };

  return code;
}
